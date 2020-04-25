#!/bin/bash

g++ -DTEST -std=c++14 -O2 -c bin.cc -o bin.o
g++ -o bin bin.o
#strip bin

