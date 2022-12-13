"The README clearly and succintly describes the following:

The linkage and location of all major code, data, results, and deliverable files.

The necessary commands to run the assignment are well described and include instructions for selecting the input dataset and output location

The test suite is well described and instructions on how to reproduce the tests are provided."

___________________________________________________________________________________________________________________________________________________

## Github Organization
Oracle-of-Artists
  - src
    - main.cpp
    - makegraph.h
    - makegraph.cpp
  - nim_graph
    - graph.h
    - graph.cpp
  - tests
    - tests.cpp
  - Makefile
  - tracks_twoartists.txt
  - results.md
  - README.md

Presentation Video


## Running Instructions
Our execution instructions are included in our Makefile. In order to run our program follow the instructions below:
In the terminal, cd to Oracle-of-Artists (or wherever this depository is stored)
Run the following instructions:
```
make exec
./bin/exec
 ```
 Then, the graph will be constructed, and our Pagerank map will be created.
 You will then be asked to input two artists.
 
 ## Running tests
 
 ```
 make tests
 ./bin/tests
 ```
 
 ## More about the test suite
 
TEST 'BFS'
  - Tests the path between "Ariana Grande" and "The Weeknd"
  - Verifies output if path is not possible

TEST 'Prim's Algorithm'
  - Tests Correct MST path created between "Ariana Grande" and "The Weeknd"

TEST 'Page Rank'
 - Test whether "Ariana Grande" has the correct popularity
 - Tests if "The Weeknd" has the correct popularity number

