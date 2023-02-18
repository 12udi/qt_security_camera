#!/bin/sh
export DISPLAY=:0
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/qt6/lib/:/usr/local/lib/aarch64-linux-gnu
export GST_PLUGIN_PATH=~/libcamera/build/src/gstreamer

# Debug Mode for GSTREAM
#GST_DEBUG=4 G_DEBUG=fatal-criticals gdb -ex run --args ./qt-cam-app &

./qt-cam-app &
python main.py
