#!/bin/sh

cd ./out
exclude_dir="/usr/include/c++"
lcov -c -d . -o apd_p2p.lcov
lcov --remove apd_p2p.lcov '/usr/include/c++/*' -o apd_p2p2.lcov
genhtml -o ./apd_p2p_cov  apd_p2p2.lcov
