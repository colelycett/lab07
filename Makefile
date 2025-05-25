CXX = g++
CXXFLAGS = --std=c++11 -Wall -Werror

test: lab07Test
	./lab07Test

lab07Test: lab07Test.o tddFuncs.o WordCount.o
	${CXX} ${CXXFLAGS} $^ -o $@

clean:
	rm -f lab07Test *.o