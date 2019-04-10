/* -*- c++ -*- */
/* 
 * Copyright 2019 Johan Jacobs.
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


#ifndef INCLUDED_MUSIC_V2_MUSIC_V2_CPP_CF_H
#define INCLUDED_MUSIC_V2_MUSIC_V2_CPP_CF_H

#include <music_v2/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace music_v2 {

    /*!
     * \brief <+description of block+>
     * \ingroup music_v2
     *
     */
    class MUSIC_V2_API music_v2_cpp_cf : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<music_v2_cpp_cf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of music_v2::music_v2_cpp_cf.
       *
       * To avoid accidental use of raw pointers, music_v2::music_v2_cpp_cf's
       * constructor is in a private implementation
       * class. music_v2::music_v2_cpp_cf::make is the public interface for
       * creating new instances.
       */
      static sptr make(int numAnt, int numSamp, int numSrc, float distance, float freq);
    };

  } // namespace music_v2
} // namespace gr

#endif /* INCLUDED_MUSIC_V2_MUSIC_V2_CPP_CF_H */

