simple_test.out: simple_testrunner.cpp count_if_followed_by.o
	g++ -o simple_test.out -I ../../info/cxxtest/ simple_testrunner.cpp count_if_followed_by.o

count_if_followed_by.o: count_if_followed_by.cpp
	g++ -c -o count_if_followed_by.o count_if_followed_by.cpp

simple_testrunner.cpp: simple.cxxtest.cpp
	../../info/cxxtest/cxxtestgen.py --error-printer -o simple_testrunner.cpp simple.cxxtest.cpp

clean:
	rm -rf simple_test.out count_if_followed_by.o
