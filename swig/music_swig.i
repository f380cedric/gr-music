/* -*- c++ -*- */

#define MUSIC_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "music_swig_doc.i"

%{
#include "music/music_cf.h"
%}

%include "music/music_cf.h"
GR_SWIG_BLOCK_MAGIC2(music, music_cf);
