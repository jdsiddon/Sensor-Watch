#!/bin/sh
set -e
make clean 
emmake make
python3 -m http.server 8000 -d build 
