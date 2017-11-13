main_ut: out_dir add_ut.o sub_ut.o
	g++ -o src/out/add_ut.o out/sub_ut.o -fprofile-arcs -ftest-coverage -lgcov -lgtest -lgtest_main -lgmock_main
add_ut.o : src/add/add_ut.cpp
	g++ -c src/add/add_ut.cpp -o out/add_ut.o -fprofile-arcs -ftest-coverage
sub.o: src/sub/sub.cpp
	g++ -c src/sub/sub_ut.cpp -o out/sub_ut.o -fprofile-arcs -ftest-coverage

out_dir:
	mkdir -p out

clean:
	-rm -rf out
	rm -rf main
