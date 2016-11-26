#!/bin/bash

set -e
set -o pipefail

start_dir=$PWD
build_dir="./build"


# perl
if [[ -d "$build_dir" ]]; then
    rm -rf $build_dir
fi

mkdir $build_dir
cd $build_dir
cmake -DUNIT_TEST=OFF -DSWIG_PERL=ON -DCMAKE_CXX_FLAGS=-fPIC ..
make clean
make -j 2
cd ..
cp build/lib/libPerlFastaReader.so Perl/libFastaReader.so
perl Perl/fasta_stats.pl -f test/data/masked.fa

cd $start_dir

