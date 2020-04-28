/* -*- c++ -*- */
/*
 * Copyright 2020 "Johan Jacobs & Cédric Hannotier".
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "music_cf_impl.h"
#include <iostream>
#include <armadillo>
#include <complex>
#include <cmath>
#include <random>
#include <tuple>


using namespace arma;

namespace gr {
  namespace music {

    music_cf::sptr
    music_cf::make(int numAnt, int numSamp, int numSrc, float distance, float freq)
    {
      return gnuradio::get_initial_sptr
        (new music_cf_impl(numAnt, numSamp, numSrc, distance, freq));
    }


    /*
     * The private constructor
     */
    music_cf_impl::music_cf_impl(int numAnt, int numSamp, int numSrc, float distance, float freq)
      : gr::sync_decimator("music_cf",
              gr::io_signature::make(1, numAnt, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(float)), numSamp),
        d_numAnt(numAnt),
        d_numSamp(numSamp),
        d_numSrc(numSrc),
        d_distance(distance),
        d_freq(freq)
    {}

    /*
     * Our virtual destructor.
     */
    music_cf_impl::~music_cf_impl()
    {
    }

    int
    music_cf_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      //const gr_complex *in = (const gr_complex *) input_items[0];
      // !!! gr_complex *out = (gr_complex *) output_items[0];
      float *out = (float *) output_items[0];

      // Declare needed variables in the order in which they will be used
      double frequency = double(d_freq) * 1e6;                                // Pass frequency in MHz because GNU Radio doesn't know doubles
      arma::cx_dmat sig = zeros<cx_dmat>(d_numAnt, d_numSamp);                // Create signal matrix
      double c = 3e8;                                                         // Define velocity of light
      std::complex<double> j = 1i;                                            // Define complex variable j (make global?)
      arma::cx_dmat covar = zeros<cx_dmat>(d_numAnt, d_numAnt);               // Signal covariance matrix
      arma::cx_vec eig_vals = zeros<cx_vec>(d_numAnt);                        // Eigenvalues
      arma::cx_mat eig_vecs = zeros<cx_dmat>(d_numAnt, d_numAnt);             // Eigenvectors
      arma::uvec sorted_ind = zeros<uvec>(d_numAnt);                          // Vector with indices of eigenvalues from smallest to largest
      arma::cx_dmat noise_vecs = zeros<cx_dmat>(d_numAnt, d_numAnt-d_numSrc); // Matrix to store the noise eigenvectors
      int numAngles = 1801;                                                   // Number of different angles to look for AoA (defines precision of AoA)
      arma::dvec angles = arma::linspace(0, 180, numAngles);                 // Vector that contains angles between 0° and 180°
      arma::cx_dmat a_steer = zeros<cx_dmat>(d_numAnt, numAngles);            // Steering vector
      arma::cx_dvec spectrum = zeros<cx_dvec>(numAngles);                     // Spectrum in which we will look for AoA
      arma::cx_dvec prodRes = zeros<cx_dvec>(1);                              // Result vector of 4 matrix multiplications (temp variable)
      int maxAngleIndex;                                                      // Index in the spectrum where the maximal peak is found
      float AoA;                                                              // Angle of arival i.e. the output

      for (int m = 0; m < noutput_items; m++) {
        // Create signal matrix
        //std::cout << "Starting for loop \n" << std::endl;
        for (int n = 0; n < d_numAnt; n++) {
          // For each of the inputs create a pointer to the start of its buffer.
          const gr_complex *in = (const gr_complex *) input_items[n];
          for (int k = 0; k < d_numSamp; k++) {
            sig(n, k) = in[k];
          }
        }
        //std::cout << sig << std::endl; // sig is perfect

        // Create covariance matrix
        covar = sig*(sig.t());
        //std::cout << "Covar: \n" << covar << std::endl; // covar is perfect

        // Perform eigenvalue decomposition
        arma::eig_gen(eig_vals, eig_vecs, covar);
        //std::cout << "eig vals: \n" << eig_vals << std::endl; // correct up to 1e-14
        //std::cout << "eig vecs: \n" << eig_vecs << std::endl; 

        // Sort the eigenvalues in order to find the eigenvectors corresponding with the noise subspace.
        sorted_ind = arma::sort_index(eig_vals, "ascend");

        // Extract all eigenvectors that correspond to the noise subspace
        for (int k = 0; k < d_numAnt-d_numSrc; k++) {
          for (int l = 0; l < d_numAnt; l++) {
            noise_vecs(l, k) = eig_vecs(l, sorted_ind(k));
          }
        }
        //std::cout << noise_vecs << std::endl; 

        // Create steering vector
        for (int k = 0; k < d_numAnt; k++) {
          for (int l = 0; l < numAngles; l++) {
            a_steer(k, l) = exp(-j*(2.0*M_PI*frequency)/c*double(d_distance)*double(k)*cos(angles(l)*M_PI/180.0));
          }
        }

        // Compute MUSIC spectrum
        for (int k = 0; k < numAngles; k++) {
          prodRes = a_steer.submat(0, k, d_numAnt-1, k).t() * noise_vecs * noise_vecs.t() * a_steer.submat(0, k, d_numAnt-1, k);
          spectrum(k) = 1.0/prodRes(0);
        }

        maxAngleIndex = spectrum.index_max();
        AoA = float(angles(maxAngleIndex));

        out[m] = AoA;
        std::cout << "AoA: " << AoA << std::endl;
        //std::cout << "out[m]: " << out[m] << std::endl;
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace music */
} /* namespace gr */

