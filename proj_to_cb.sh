#!/usr/bin/env bash
rm -r share/ 2>/dev/null
mkdir share
cd share

# headers
cat ../include/tests.h >> main.cpp
cat ../include/position.h >> main.cpp
cat ../include/level.h >> main.cpp
cat ../include/js.h >> main.cpp
cat ../include/https.h >> main.cpp

# implementations
cat ../src/level.cpp >> main.cpp
cat ../src/js.cpp >> main.cpp
cat ../src/https.cpp >> main.cpp
cat ../src/trivial-solver.cpp >> main.cpp
cat ../src/main.cpp >> main.cpp


sed -i -E "s/#pragma once//" main.cpp
sed -i -E "s/#include \".+\"//" main.cpp


# compile:
g++ main.cpp -o main
