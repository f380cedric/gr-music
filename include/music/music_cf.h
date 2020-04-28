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

#ifndef INCLUDED_MUSIC_MUSIC_CF_H
#define INCLUDED_MUSIC_MUSIC_CF_H

#include <music/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace music {

    /*!
     * \brief <+description of block+>
     * \ingroup music
     *
     */
    class MUSIC_API music_cf : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<music_cf> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of music::music_cf.
       *
       * To avoid accidental use of raw pointers, music::music_cf's
       * constructor is in a private implementation
       * class. music::music_cf::make is the public interface for
       * creating new instances.
       */
      static sptr make(int numAnt, int numSamp, int numSrc, float distance, float freq);
    };

  } // namespace music
} // namespace gr

#endif /* INCLUDED_MUSIC_MUSIC_CF_H */

