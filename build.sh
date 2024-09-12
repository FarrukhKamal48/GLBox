#!/bin/bash

build_dir=build

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -B $build_dir

echo "  "

make -C $build_dir 

echo "  "
