#!/bin/bash

# Example: ./getoj.sh 1596
echo Downloading $1.pdf ...
id=$1
curl https://onlinejudge.org/external/${id::${#id}-2}/$1.pdf --output $1.pdf