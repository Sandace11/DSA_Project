#!/usr/bin/bash

build_dir=build
binary_dir=bin

if [ ! -d "$build_dir" ]; then 
  mkdir $build_dir
fi

if [ ! -d "$binary_dir" ]; then 
  mkdir $binary_dir 
fi

echo "Project initialization complete!"
