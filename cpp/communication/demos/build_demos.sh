#!/bin/bash

include_dirs=../cpp_interface/

g++ demo0.cpp -g -std=c++11 -I${include_dirs} -o demo0

g++ demo1.cpp -g -std=c++11 -I${include_dirs} -o demo1
