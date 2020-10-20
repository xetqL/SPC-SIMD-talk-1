#!/bin/zsh 
make clean
make vec novec
./vec
./novec
python plot.py
