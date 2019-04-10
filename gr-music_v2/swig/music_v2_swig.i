/* -*- c++ -*- */

#define MUSIC_V2_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "music_v2_swig_doc.i"

%{
#include "music_v2/music_v2_cpp_cf.h"
%}


%include "music_v2/music_v2_cpp_cf.h"
GR_SWIG_BLOCK_MAGIC2(music_v2, music_v2_cpp_cf);
