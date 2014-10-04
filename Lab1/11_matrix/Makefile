# Change these
cxxtestpath = ../../info/cxxtest/
testcode    = example_test.h
cxx_flags = -std=c++11 -Wall

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest0%: testcode.cpp
	g++ ${cxx_flags} -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o


clean:
	touch runtest01 testcode.cpp
	rm runtest0* testcode.cpp

