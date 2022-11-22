CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/makegraph.cpp src/main.cpp 
	${CXX} ${CXX_FLAGS} src/main.cpp src/makegraph.cpp -o bin/exec


obj/catch.o: tests/catch.cc
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*