#!/usr/bin/env bash
cd build
cmake ..
make
./tests
./main
