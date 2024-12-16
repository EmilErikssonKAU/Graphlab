# Lab: graph-based data structures
This document provides a cheat-sheet on how to work with the provided
start-code.

## Use available options
```
$ ./adjlist
USAGE: ./adjlist [flags]
	-h	-- help
	-u 	-- undirected mode
	-e	-- echo input

```

As shown above, you can specify if the program should use an (un)directed graph.
The default is directed, and you can change it by setting the undirected mode:
- Run in directed mode: `./adjlist`
- Run in undirected mode: `./adjlist -u`

When using input scripts it might be of interest to see the actual commands
echoed to the screen, this can be done by the -e flag that turns on echo.
- Run manually without echo: `./adjlist`
- Run input script with echo: `./adjlist -e < input.txt`

## Run automated tests
To verify that your implementation works as expected, you may run the unit tests
that we use to automatically grade your lab. Each test consists of several test
cases, each test case number will either be printed green for success or red
for failure, points are calculated based on the percentage of successful tests
and are both weighted and limited. 
```
# Adjacency list
test_is_empty
test_add_node
test_delete_node
test_find_node
test_node_cardinality
test_add_edge
test_add_edge_update
test_delete_edge
test_delete_edges
test_find_edge
test_edge_cardinality
test_self_loops
test_adjacency_matrix

# Algorithms
test_dijkstra
test_prim
test_warshall
test_floyd
```

Example of running all tests:
```
$ make test
cc -Wall   -c -o adjlist_test.o adjlist_test.c
gcc -Wall -o adjlist_test adjlist.o adjlist_test.o -lm
gcc -Wall -o algorithm_test algorithm_test.c adjlist.c algorithm.c -lm
----------------------------------------------------
Testing Adjacency List + Algorithms...
----------------------------------------------------

Testing Adjacency List
----------------------

Testing is_empty
 1  2  3  4
				NOT OK!
Testing add_node
 1  2  3  4  5  6  7  8  9 10
11
				NOT OK!
Testing delete_node
 1  2  3  4  5  6  7  8  9 10
11 12 13
				NOT OK!
Testing find_node
 1  2  3  4  5  6  7  8  9 10
11 12 13
				OK!
Testing node_cardinality
 1  2  3  4  5  6  7  8  9 10
11
				NOT OK!
Testing add_edge
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16 17 18 19 20
21 22
				NOT OK!
Testing upd_edge
 1  2  3  4  5  6  7  8  9
				NOT OK!
Testing rem_edge
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16 17 18 19 20
21
				NOT OK!
Testing rem_edges
 1  2  3  4  5  6  7  8  9
				NOT OK!
Testing find_edge
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24
				OK!
Testing edge_cardinality
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16
				NOT OK!
Testing self_loops
 1  2  3  4  5  6  7  8  9 10

				NOT OK!
Testing adjacency_matrix
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16
				NOT OK!
				0.0p

Testing Algorithms
------------------

Testing Dijkstra
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27
				NOT OK!
Testing Prim
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
31 32 33 34 35
				NOT OK!
Testing Floyd
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16 17 18
				NOT OK!
Testing Warshall
 1  2  3  4  5  6  7  8  9 10
11 12 13 14 15 16 17 18
				NOT OK!
				0.0p
Code Quality (manual)		   p
```
----------------------------------------------------------------------
Example of running only adjacency list tests:
```
$ make adjlist_test
$ ./adjlist_test

----------------------------------------------------------------------
Example of running only algorithm tests:
```
$ make algorithm_test
$ ./algorithm_test

----------------------------------------------------------------------
