单元测试和代码覆盖的框架

cd ./unittest
make
./run_test
./launch.sh
cd out/test_gcover


lcov默认不统计分支覆盖了，需要修改配置文件
通过源代码安装的在 /usr/local/etc/lcovrc
lcov_branch_coverage改为1后，ok 
