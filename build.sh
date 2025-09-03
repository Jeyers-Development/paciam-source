#!/bin/bash

cd build
cmake --build .

cd ..
read -p "~> " command
$command