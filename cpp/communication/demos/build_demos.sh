#!/bin/bash

include_dirs=../cpp_interface/

g++ demo0.cpp -std=c++11 -I${include_dirs} -o demo0

g++ demo1.cpp -std=c++11 -I${include_dirs} -o demo1

g++ demo2.cpp -std=c++11 -I${include_dirs} -o demo2
