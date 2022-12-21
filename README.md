
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
https://www.youtube.com/watch?v=bR9_4GnOb6A


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
 For Artist 1 input: Taylor Swift
 For Artist 2 input: Ariana Grande
 
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

TEST 'Betweeness Centrality'
  - Confirms the correctness of “bacon tables” for artists “The Weeknd”, “Ariana Grande”, and “Idina Menzel”

TEST 'Connected Components'
  - Checks if the graph contains the correct number of connected components

