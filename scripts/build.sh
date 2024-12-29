#!/bin/bash

build_dir=build

cmake -G "Unix Makefiles" -B $build_dir

echo "  "

make -C $build_dir 

echo "  "
