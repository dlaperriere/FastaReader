#!/bin/bash

set -e
set -o pipefail

start_dir=$PWD
build_dir="./build"


# python
if [[ -d "$build_dir" ]]; then
    rm -rf $build_dir
fi

py=/usr/bin/python3.8

mkdir $build_dir
cd $build_dir
cmake -DUNIT_TEST=OFF -DSWIG_PYTHON=ON -DCMAKE_CXX_FLAGS=-fPIC -DPYTHON_EXECUTABLE=$py ..
make clean
make -j 2
cd ..

cp build/lib/_PythonFastaReader.so Python/_PythonFastaReader.so
$py Python/fasta_stats.py -f test/data/masked.fa

cd $start_dir

