#!/bin/sh

out_dir=../unittest/out

cd ../src
rm -rf $out_dir
mkdir -p $out_dir

exclude_dir="/usr/include/c++"

lcov -c -d . -o ${out_dir}/test.lcov
lcov --remove ${out_dir}/test.lcov '/usr/include/c++/*' -o ${out_dir}/test2.lcov
genhtml -o ${out_dir}/test_gcover  ${out_dir}/test.lcov
rm -f ${out_dir}/test.lcov
rm -f ${out_dir}/test2.lcov
