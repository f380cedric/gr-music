#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2019 Johan Jacobs.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import music_v2_swig as music_v2
import numpy as np
import math
import cmath

class qa_music_v2_cpp_cf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # Create inputs and variables
        numAnt = 4;
        numSamp = 10;
        numSrc = 1;
        d = 0.06;
        frequency = 2500; # MHz !
        freq = 2.5e9; # GHz for creating signals

        # Constants
        c = 3.0e8;
        theta = math.pi/8;
        
        # Create sinusoidal input
        t_end = 3.0/freq;       # 3 signal periods
        t = np.linspace(0, t_end-t_end/numSamp, numSamp)
        sig0 = [None]*numSamp
        sig1 = [None]*numSamp
        sig2 = [None]*numSamp
        sig3 = [None]*numSamp
        for k in range(numSamp):
            sig0[k] = math.cos(2*math.pi*freq*t[k])
        
        for k in range(numSamp):
            sig1[k] = sig0[k]*cmath.exp(-1j*2*math.pi*freq*1*d*math.cos(theta)/c)
            sig2[k] = sig0[k]*cmath.exp(-1j*2*math.pi*freq*2*d*math.cos(theta)/c)
            sig3[k] = sig0[k]*cmath.exp(-1j*2*math.pi*freq*3*d*math.cos(theta)/c)          

        
        expected = (22.5,)
        

        # Create blocks
        src0 = blocks.vector_source_c(sig0)
        src1 = blocks.vector_source_c(sig1)
        src2 = blocks.vector_source_c(sig2)
        src3 = blocks.vector_source_c(sig3)
        myblock = music_v2.music_v2_cpp_cf(numAnt, numSamp, numSrc, d, frequency)
        dst = blocks.vector_sink_f()

        # Connect
        self.tb.connect(src0, (myblock, 0))
        self.tb.connect(src1, (myblock, 1))
        self.tb.connect(src2, (myblock, 2))
        self.tb.connect(src3, (myblock, 3))
        self.tb.connect(myblock, dst)
        
        # Run
        self.tb.run()
        
        # Check data
        result = dst.data()
        self.assertTupleEqual(expected, result)
        #self.assertEqual(len(expected), len(result)) # float has no len, but both variables have len=1


if __name__ == '__main__':
    gr_unittest.run(qa_music_v2_cpp_cf, "qa_music_v2_cpp_cf.xml")
