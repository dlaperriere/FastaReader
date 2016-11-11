#!/bin/bash

set -e
set -o pipefail

start_dir=$PWD
build_dir="./build"


# python
if [[ -d "$build_dir" ]]; then
    rm -rf $build_dir
fi

mkdir $build_dir
cd $build_dir
cmake -DUNIT_TEST=OFF -DSWIG_PYTHON=ON -DCMAKE_CXX_FLAGS=-fPIC -DPYTHON_EXECUTABLE=/usr/bin/python3 ..
make clean
make
cd ..

cp build/lib/_PythonFastaReader.so Python/_FastaReader.so
python3 Python/fasta_stats.py -f test/data/masked.fa

cd $start_dir

