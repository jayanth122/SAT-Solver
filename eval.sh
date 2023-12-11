#!/bin/bash

mkdir build && cd build && cmake ../ && make

./pa2 < ../test/test0.in > test_your.out # output your answer
diff ../test/test0.out test_your.out


