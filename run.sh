#!/usr/bin/env bash
cd build
cmake ..
make -j$(nproc)
echo "-------------------------"
./tests
echo "-------------------------"
./main $1
