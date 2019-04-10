#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/python
export PATH=/home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/build/python:$PATH
export LD_LIBRARY_PATH=/home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/build/swig:$PYTHONPATH
/usr/bin/python2 /home/johan/Documents/GNU_Radio_Tutorials/Work/gr-music_v2/python/qa_music_v2_cpp_cf.py 
