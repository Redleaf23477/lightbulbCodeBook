#!/bin/bash

# build list.tex

echo 'building list.tex...'

rm a.out
g++-8 -std=c++11 -O2 GenCodebookList.cpp
./a.out

echo 'done'

# build codebook.pdf

echo 'rendering codebook.pdf...'

xelatex Codebook.tex
xelatex Codebook.tex

echo 'done'
