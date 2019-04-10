#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/lib
export PATH=/home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/build/lib:$PATH
export LD_LIBRARY_PATH=/home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-music_v2 
