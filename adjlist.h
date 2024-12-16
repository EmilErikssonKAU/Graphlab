// adjlist.h
#ifndef _ADJLIST_H
#define _ADJLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#define MAXNODES 32
// pedge - pointer to an edge
typedef struct edge *pedge;
// edge - defines an edge structure
typedef struct edge {
	double weight;    // weight of edge
	char to;          // end node
	//char from;
	pedge next_edge;
} edge;

// pnode - pointer to a node
typedef struct node *pnode;
// node - defines a node structure, used for making adjacency lists
typedef struct node {
	char name;        // name of node
	double d;         // only used in algorithms for distance
	char pi;          // only used in algorithms for neighbor
	pedge edges;      // pointer to first (if any) edge from node
	pnode next_node;  // pointer to next node (if any) in adjlist
} node;
bool is_empty(pnode G);
char get_name(pnode G);
pnode get_next(pnode G);
pedge get_edges(pnode G);
double get_d(pnode G);
char get_pi(pnode G);
pnode set_name(pnode G, char name);
pnode set_edges(pnode G, pedge E);
pnode set_d(pnode G, double d);
pnode set_pi(pnode G, char pi);
pnode add_node(pnode G, char nname);
pnode rem_node(pnode G, char name);
pnode get_node(pnode G, char name);
bool find_node(pnode G, char name);
void add_edge(pnode G, char from, char to, double weight);
void rem_edge(pnode G, char from, char to);
bool find_edge(pnode G, char from, char to);
int node_cardinality(pnode G);
int edge_cardinality(pnode G);
int name_to_pos(pnode G, char c);
char pos_to_name(pnode G, int pos);
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES]);
int self_loops(pnode G);
#endif
