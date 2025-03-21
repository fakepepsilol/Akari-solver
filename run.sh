#!/usr/bin/env bash
cd build
cmake ..
make
echo "-------------------------"
./tests
echo "-------------------------"
./main
