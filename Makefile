CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/makegraph.cpp src/main.cpp nim_graph/graph.cpp 
	${CXX} ${CXX_FLAGS} src/main.cpp src/makegraph.cpp nim_graph/graph.cpp -o bin/exec

bin/main: src/makegraph.cpp src/main.cpp nim_graph/graph.cpp 
	${CXX} ${CXX_FLAGS} src/main.cpp src/makegraph.cpp nim_graph/graph.cpp -o bin/exec

obj/catch.o: tests/catch.cc
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

bin/tests: tests/tests.cpp src/makegraph.cpp nim_graph/graph.cpp
	${CXX} ${CXX_FLAGS} tests/tests.cpp src/makegraph.cpp nim_graph/graph.cpp -o bin/tests

.DEFAULT_GOAL := tests
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*