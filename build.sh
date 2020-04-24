#!/bin/bash

g++ -std=c++1y -O2 -c bin.cc -o bin.o
g++ -o bin bin.o
#strip bin