#!/bin/bash

python input.py
echo "O(nlogn)"
clang++ a3.cpp
/usr/bin/time -p ./a.out
echo "O(n2)"
clang++ a3_brute.cpp
/usr/bin/time -p ./a.out
