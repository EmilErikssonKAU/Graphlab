#include <stdio.h>
#include <stdbool.h>
#include "adjlist.h"
#define NEMPTY 4
#define NADD 11
#define NDEL 13
#define NFIND 13
#define NEDGE 22
#define NUPED 9
#define NREMED 21
#define NREMEDS 9
#define NFINDE 24
#define NCARDE 16
#define NLOOP 10
#define NMAT 16
#define RESET   	"\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
typedef float (*test_func)();
typedef struct empty_test{
	int size;
	char adds[MAXNODES];
	bool empty;
}empty_test;
typedef struct delete_test{
	int size_add;
	char adds[MAXNODES];
	char del;
	int del_size;
	char remain[MAXNODES];
}delete_test;
typedef struct find_test{
	int size;
	char adds[MAXNODES];
	char find;
	bool exists;
}find_test;
typedef struct an_edge{
	char from;
	char to;
	int weight;
}an_edge;
typedef struct edge_test{
	int size_add;
	char adds[MAXNODES];
	int size_edge;
	an_edge add_edges[MAXNODES*MAXNODES];
	int size_act;
	an_edge act_edges[MAXNODES*MAXNODES];
	bool exists;
}edge_test;
typedef struct edge_id{
	char from;
	char to;
}edge_id;
typedef struct edge_rem_test{
	int size_add;
	char adds[MAXNODES];
	int size_edge;
	an_edge add_edges[MAXNODES*MAXNODES];
	int size_rem;
	edge_id rem_edges[MAXNODES*MAXNODES];
	int size_act;
	an_edge act_edges[MAXNODES*MAXNODES];
}edge_rem_test;
typedef struct edge_card_test{
	int size_add;
	char adds[MAXNODES];
	int size_edge;
	an_edge add_edges[MAXNODES*MAXNODES];
	int card;
}edge_card_test;
typedef struct list_to_matrix_test{
	int size_add;
	char adds[MAXNODES];
	int size_edge;
	an_edge add_edges[MAXNODES*MAXNODES];
	double matrix[MAXNODES][MAXNODES];
}list_to_matrix_test;
//--------------------------------------------------------------------------
// empty tests
empty_test empty_t[NEMPTY] =	{	{0, {},				true},
								{1, {'a'},			false},
								{2, {'a','b'},		false},
								{1, {'b','a'},		false},
							};
//--------------------------------------------------------------------------
// add tests
empty_test add_t[] =		{
								{0, {},					true},
								{1, {'a'}, 				false},
								{2, {'a','b'}, 			false},
								{2, {'b','a'}, 			false},
								{3, {'a','b','c'}, 		false},
								{3, {'a','c','b'}, 		false},
								{3, {'b','a','c'}, 		false},
								{3, {'b','c','a'}, 		false},
								{3, {'c','a','b'}, 		false},
								{3, {'c','b','a'}, 		false},
								{4, {'d','c','b','a'}, 	false}
							};
delete_test del_t[] =  	{
								{0,	{}, 			'a', 0,	{}},
								{1,	{'a'}, 			'a', 0,	{}},
								{1,	{'a'}, 			'b', 1,	{'a'}},
								{1,	{'a'}, 			'B', 1,	{'a'}},
								{2,	{'a','b'}, 		'a', 1,	{'b'}},
								{2,	{'a','b'}, 		'b', 1,	{'a'}},
								{2,	{'a','b'}, 		'c', 2,	{'a','b'}},
								{2,	{'a','b'}, 		'C', 2,	{'a','b'}},
								{3,	{'a','b','c'}, 	'a', 2,	{'b','c'}},
								{3, {'a','b','c'}, 	'b', 2,	{'a','c'}},
								{3, {'a','b','c'}, 	'c', 2,	{'a','b'}},
								{3, {'a','b','c'}, 	'd', 3,	{'a','b','c'}},
								{3, {'a','b','c'}, 	'D', 3,	{'a','b','c'}},
							};
find_test find_t[] =	{
								{0, {}, 			'a', 	false},
								{1, {'a'}, 			'a', 	true},
								{1, {'a'}, 			'b', 	false},
								{1, {'a'}, 			'B', 	false},
								{2, {'a','b'}, 		'a', 	true},
								{2, {'a','b'}, 		'b', 	true},
								{2, {'a','b'}, 		'c', 	false},
								{2, {'a','b'}, 		'C', 	false},
								{3, {'a','b','c'}, 	'a', 	true},
								{3, {'a','b','c'}, 	'b', 	true},
								{3, {'a','b','c'}, 	'c', 	true},
								{3, {'a','b','c'}, 	'd', 	false},
								{3, {'a','b','c'}, 	'D', 	false},
							};
edge_test add_edge_t[] = {
        // no nodes
        {0, {}, 1, {{'a','a',1}}, 0, {{}}},
        {0, {}, 1, {{'a','b',1}}, 0, {{}}},
        {0, {}, 1, {{'b','a',1}}, 0, {{}}},
        // 1 node
        {1, {'a'}, 0, {{}}, 0, {{}}},
        {1, {'a'}, 1, {{'a','a',1}}, 1, {{'a','a',1}}},
        {1, {'a'}, 1, {{'a','b',1}}, 0, {{}}},
        {1, {'a'}, 1, {{'b','a',1}}, 0, {{}}},
    	// 2 nodes
        {2, {'a','b'}, 0, {{}}, 0, {{}}},
        {2, {'a','b'}, 1, {{'a','a',1}}, 1, {{'a','a',1}}},
        {2, {'a','b'}, 2, {{'a','a',1}, {'a','a',1}}, 1, {{'a','a',1}}},
        {2, {'a','b'}, 2, {{'a','a',1}, {'a','b',1}}, 2, {{'a','a',1},{'a','b',1}}},
        {2, {'a','b'}, 3, {{'a','a',1}, {'a','b',1},{'b','a',1}}, 3, {{'a','a',1},{'a','b',1},{'b','a',1}}},
        // 3 nodes
        {3, {'a','b','c'}, 0, {}, 0, {}},
        {3, {'a','b','c'}, 1, {{'a','a',1}}, 1, {{'a','a',1}}},
        {3, {'a','b','c'}, 2, {{'a','a',1},{'a','b',1}}, 2, {{'a','a',1},{'a','b',1}}},
        {3, {'a','b','c'}, 3, {{'a','a',1},{'a','b',1},{'a','c',1}}, 3, {{'a','a',1},{'a','b',1},{'a','c',1}}},
        {3, {'a','b','c'}, 4, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1}}, 4, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1}}},
        {3, {'a','b','c'}, 5, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1}}, 5, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1}}},
        {3, {'a','b','c'}, 6, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1}}, 6, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1}}},
        {3, {'a','b','c'}, 7, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1}}, 7, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1}}},
        {3, {'a','b','c'}, 8, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1}}, 8, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1}}},
        {3, {'a','b','c'}, 9, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 9, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}},
    };
edge_test upd_edge_t[] = {
			// 1 node
			{1, {'a'}, 0, {{}}, 0, {{}}},
			{1, {'a'}, 2, {{'a','a',1},{'a','a',2}}, 1, {{'a','a',2}}},
			// 2 nodes
			{2, {'a','b'}, 2, {{'a','a',1}, {'a','a',2}}, 1, {{'a','a',2}}},
			{2, {'a','b'}, 4, {{'a','a',1}, {'a','b',1},{'b','a',1}, {'a','a',2}}, 3, {{'a','a',2},{'a','b',1},{'b','a',1}}},
			{2, {'a','b'}, 4, {{'a','a',1}, {'a','b',1},{'b','a',1}, {'a','b',2}}, 3, {{'a','a',1},{'a','b',2},{'b','a',1}}},
			{2, {'a','b'}, 4, {{'a','a',1}, {'a','b',1},{'b','a',1}, {'b','a',2}}, 3, {{'a','a',1},{'a','b',1},{'b','a',2}}},
			// 3 nodes
			{3, {'a','b','c'}, 4, {{'a','b',1},{'b','b',1},{'b','c',1},{'a','b',2}}, 3, {{'a','b',2},{'b','b',1},{'b','c',1}}},
			{3, {'a','b','c'}, 4, {{'a','b',1},{'b','b',1},{'b','c',1},{'b','b',2}}, 3, {{'a','b',1},{'b','b',2},{'b','c',1}}},
			{3, {'a','b','c'}, 4, {{'a','b',1},{'b','b',1},{'b','c',1},{'b','c',2}}, 3, {{'a','b',1},{'b','b',1},{'b','c',2}}},
		};
edge_rem_test rem_edge_t[] = {
	// empty
	{0, {},0,{{}},1, {{'a','a'}},0, {{}}},
	// 1 node
	{1, {'a'},0, {{}},1, {{'a','a'}},0, {{}}},
	{1, {'a'},1, {{'a','a',1}},1, {{'a','a'}},0,{{}}},
	{1, {'a'},1, {{'a','a',1}},1, {{'a','b'}},1, {{'a','a',1}}},
	{1, {'a'},1, {{'a','a',1}},1, {{'b','a'}},1, {{'a','a',1}}},
	// 2 nodes
	{2, {'a','b'}, 4, {{'a','a',1},{'a','b',1},{'b','a',1},{'b','b',1}}, 1, {{'a','a'}}, 3, {{'a','b',1},{'b','a',1},{'b','b',1}}},
	{2, {'a','b'}, 4, {{'a','a',1},{'a','b',1},{'b','a',1},{'b','b',1}}, 1, {{'a','b'}}, 3, {{'a','a',1},{'b','a',1},{'b','b',1}}},
	{2, {'a','b'}, 4, {{'a','a',1},{'a','b',1},{'b','a',1},{'b','b',1}}, 1, {{'b','a'}}, 3, {{'a','a',1},{'a','b',1},{'b','b',1}}},
	{2, {'a','b'}, 4, {{'a','a',1},{'a','b',1},{'b','a',1},{'b','b',1}}, 1, {{'b','b'}}, 3, {{'a','a',1},{'a','b',1},{'b','a',1}}},
	{2, {'a','b'}, 3, {{'a','b',1},{'b','a',1},{'b','b',1}}, 1, {{'a','b'}}, 2, {{'b','a',1},{'b','b',1}}},
	{2, {'a','b'}, 2, {{'b','a',1},{'b','b',1}},1, {{'b','a'}}, 1, {{'b','b',1}}},
	{2, {'a','b'}, 1, {{'b','b',1}}, 1, {{'b','b'}}, 0, {{}}},
	// 3 nodes
	{3, {'a','b','c'}, 9, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1, {{'a','a'}}, 8, {{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1, {{'a','b'}}, 8,  {{'a','a',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1,{{'a','c'}}, 8, {{'a','a',1},{'a','b',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9,  {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1,{{'b','a'}}, 8, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9,  {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1, {{'b','b'}}, 8, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1, {{'b','c'}}, 8, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'c','a',1},{'c','b',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9,  {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1, {{'c','a'}}, 8, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','b',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9,  {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1,{{'c','b'}}, 8,  {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','c',1}}},
	{3, {'a','b','c'}, 9, {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1},{'c','c',1}}, 1,{{'c','c'}}, 8,  {{'a','a',1},{'a','b',1},{'a','c',1},{'b','a',1},{'b','b',1},{'b','c',1},{'c','a',1},{'c','b',1}}},
	};
edge_rem_test rem_edges_t[] = {
    // empty
    {0, {}, 0, {}, 1, {{'a', 'a'}}, 0, {}},

    // 1 node
    {1, {'a'}, 0, {}, 1, {{'a', 'a'}}, 0, {}},
    {1, {'a'}, 1, {{'a', 'a', 1}}, 1, {{'a', 'a'}}, 0, {}},
    // {1, {'a'}, 1, {{'a', 'a', 1}}, 1, {{'b', 'b'}}, 1, {{'a', 'a', 1}}},

    // 2 nodes
    {2, {'a', 'b'}, 4, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}, {'b', 'b', 1}}, 1, {{'a', 'b'}}, 2, {{'a', 'b', 1}, {'b', 'b', 1}}},
    {2, {'a', 'b'}, 4, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}, {'b', 'b', 1}}, 1, {{'b', 'a'}}, 2, {{'a', 'a', 1}, {'b', 'a', 1}}},
    {2, {'a', 'b'}, 4, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}, {'b', 'b', 1}}, 1, {{'c', 'c'}}, 4, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}, {'b', 'b', 1}}},

    // 3 nodes
    {3, {'a', 'b', 'c'}, 9, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}, {'c', 'c', 1}}, 1, {{'a', 'a'}}, 6, {{'a', 'b', 1}, {'a', 'c', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'b', 1}, {'c', 'c', 1}}},
    {3, {'a', 'b', 'c'}, 9, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}, {'c', 'c', 1}}, 1, {{'b', 'b'}}, 6, {{'a', 'a', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'c', 1}}},
    {3, {'a', 'b', 'c'}, 9, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}, {'c', 'c', 1}}, 1, {{'c', 'c'}}, 6, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'c', 'a', 1}, {'c', 'b', 1}}}
};
edge_test find_edge_t[] = {
    // Empty nodes and edges
    {0, {}, 0, {}, 1, {{'a', 'a', 0}}, false},
    {0, {}, 0, {}, 1, {{'a', 'b', 0}}, false},
    {0, {}, 0, {}, 1, {{'b', 'a', 0}}, false},

    // Single node
    {1, {'a'}, 0, {}, 1, {{'a', 'a', 0}}, false},
    {1, {'a'}, 0, {}, 1, {{'a', 'b', 0}}, false},
    {1, {'a'}, 0, {}, 1, {{'b', 'a', 0}}, false},
    {1, {'a'}, 1, {{'a', 'a', 1}}, 1, {{'a', 'a', 1}}, true},
    {1, {'a'}, 1, {{'a', 'a', 1}}, 1, {{'a', 'b', 0}}, false},
    {1, {'a'}, 1, {{'a', 'a', 1}}, 1, {{'b', 'a', 0}}, false},

    // Two nodes
    {2, {'a', 'b'}, 0, {}, 1, {{'a', 'a', 0}}, false},
    {2, {'a', 'b'}, 0, {}, 1, {{'a', 'b', 0}}, false},
    {2, {'a', 'b'}, 0, {}, 1, {{'b', 'a', 0}}, false},
    {2, {'a', 'b'}, 2, {{'a', 'b', 1}, {'b', 'b', 1}}, 1, {{'a', 'a', 0}}, false},
    {2, {'a', 'b'}, 2, {{'a', 'b', 1}, {'b', 'b', 1}}, 1, {{'a', 'b', 1}}, true},
    {2, {'a', 'b'}, 2, {{'a', 'b', 1}, {'b', 'b', 1}}, 1, {{'b', 'b', 1}}, true},
    {2, {'a', 'b'}, 2, {{'a', 'b', 1}, {'b', 'b', 1}}, 1, {{'b', 'a', 0}}, false},

    // Three nodes
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'a', 'a', 1}}, true},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'a', 'b', 1}}, true},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'a', 'c', 0}}, false},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'b', 'a', 0}}, false},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'b', 'b', 1}}, true},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'b', 'c', 1}}, true},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'c', 'a', 1}}, true},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}}, 1, {{'c', 'b', 0}}, false}
};
edge_card_test edge_card_t[] = {
    // Empty nodes and edges
    {0,{}, 0, {}, 0},

    // One node, no edges
    {1, {'a'}, 0, {}, 0},

    // Two nodes, no edges
    {2,{'a', 'b'}, 0, {}, 0},

    // One node, one self-loop
    {1, {'a'}, 1, {{'a', 'a', 1}}, 1},

    // Two nodes, one edge
    {2, {'a', 'b'}, 1, {{'a', 'a', 1}}, 1},

    // Two nodes, two edges
    {2, {'a', 'b'}, 2, {{'a', 'a', 1}, {'a', 'b', 1}}, 2},
    {2, {'a', 'b'}, 2, {{'a', 'a', 1}, {'b', 'a', 1}}, 2},
    {2, {'a', 'b'}, 2, {{'a', 'a', 1}, {'b', 'b', 1}}, 2},

    // Two nodes, three edges
    {2, {'a', 'b'}, 3, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}}, 3},
    {2, {'a', 'b'}, 3, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}}, 3},
    {2, {'a', 'b'}, 3, {{'a', 'a', 1}, {'b', 'a', 1}, {'b', 'b', 1}}, 3},

    // Two nodes, four edges
    {2, {'a', 'b'}, 4, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}, {'b', 'b', 1}}, 4},

    // Three nodes, five edges
    {3, {'a', 'b', 'c'}, 5, {{'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'c', 1}}, 5},

    // Three nodes, six edges
    {3, {'a', 'b', 'c'}, 6, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'c', 1}}, 6},

    // Three nodes, seven edges
    {3, {'a', 'b', 'c'}, 7, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'c', 1}}, 7},

    // Three nodes, eight edges
    {3, {'a', 'b', 'c'}, 8, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'c', 1}}, 8},

    // Three nodes, nine edges
    {3, {'a', 'b', 'c'}, 9, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}, {'c', 'c', 1}}, 9}
};
edge_card_test self_loop_t[] = {
    // Empty nodes and edges
    {0, {}, 0, {{}}, 0},

    // One node, no edges
    {1, {'a'}, 0, {{}}, 0},

    // One node, one self-loop
    {1, {'a'}, 1, {{'a', 'a', 1}}, 1},

    // Two nodes, one edge
    {2, {'a', 'b'}, 1, {{'a', 'a', 1}}, 1},

    // Two nodes, three edges
    {2, {'a', 'b'}, 3, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}}, 1},

    // Two nodes, four edges
    {2, {'a', 'b'}, 4, {{'a', 'a', 1}, {'a', 'b', 1}, {'b', 'a', 1}, {'b', 'b', 1}}, 2},

    // Three nodes, six edges, no self-loop
    {3, {'a', 'b', 'c'}, 6, {{'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}}, 0},

    // Three nodes, seven edges, one self-loop
    {3, {'a', 'b', 'c'}, 7, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}}, 1},

    // Three nodes, eight edges, two self-loops
    {3, {'a', 'b', 'c'}, 8, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}}, 2},

    // Three nodes, nine edges, three self-loops
    {3, {'a', 'b', 'c'}, 9, {{'a', 'a', 1}, {'a', 'b', 1}, {'a', 'c', 1}, {'b', 'a', 1}, {'b', 'b', 1}, {'b', 'c', 1}, {'c', 'a', 1}, {'c', 'b', 1}, {'c', 'c', 1}}, 3}
};
list_to_matrix_test list_matrix_t[] = {
    // No edges
    {0, {}, 0, {}, {{}}},
    {1, {'a'}, 0, {}, {{INFINITY}}},
    {2, {'a', 'b'}, 0, {}, {{INFINITY, INFINITY}, {INFINITY, INFINITY}}},
    {3, {'a', 'b', 'c'}, 0, {}, {{INFINITY, INFINITY, INFINITY}, {INFINITY, INFINITY, INFINITY}, {INFINITY, INFINITY, INFINITY}}},

    // With edges (1 node)
    {1, {'a'}, 1, {{'a', 'a', 1}}, {{1}}},
    {1, {'a'}, 1, {{'a', 'a', 2}}, {{2}}},

    // With edges (2 nodes)
    {2, {'a', 'b'}, 1, {{'a', 'a', 1}}, {{1, INFINITY}, {INFINITY, INFINITY}}},
    {2, {'a', 'b'}, 2, {{'a', 'a', 1}, {'a', 'b', 2}}, {{1, 2}, {INFINITY, INFINITY}}},
    {2, {'a', 'b'}, 3, {{'a', 'a', 1}, {'a', 'b', 2}, {'b', 'a', 3}}, {{1, 2}, {3, INFINITY}}},
    {2, {'a', 'b'}, 4, {{'a', 'a', 1}, {'a', 'b', 2}, {'b', 'a', 3}, {'b', 'b', 4}}, {{1, 2}, {3, 4}}},
    {2, {'a', 'b'}, 3, {{'a', 'b', 2}, {'b', 'a', 3}, {'b', 'b', 4}}, {{INFINITY, 2}, {3, 4}}},
    {2, {'a', 'b'}, 2, {{'b', 'a', 3}, {'b', 'b', 4}}, {{INFINITY, INFINITY}, {3, 4}}},
    {2, {'a', 'b'}, 1, {{'b', 'b', 4}}, {{INFINITY, INFINITY}, {INFINITY, 4}}},

    // With edges (3 nodes)
    {3, {'a', 'b', 'c'}, 3, {{'a', 'a', 9}, {'b', 'b', 2}, {'c', 'c', 13}}, {{9, INFINITY, INFINITY}, {INFINITY, 2, INFINITY}, {INFINITY, INFINITY, 13}}},
    {3, {'a', 'b', 'c'}, 5, {{'a', 'a', 9}, {'a', 'c', 1}, {'b', 'b', 2}, {'c', 'a', 7}, {'c', 'c', 13}}, {{9, INFINITY, 1}, {INFINITY, 2, INFINITY}, {7, INFINITY, 13}}},

    // With edges (4 nodes)
    {4, {'a', 'b', 'c', 'd'}, 6, {{'a', 'b', 1}, {'b', 'a', 4}, {'b', 'd', 2}, {'c', 'c', 11}, {'d', 'a', 3}, {'d', 'b', 1}},
        {{INFINITY, 1, INFINITY, INFINITY}, {4, INFINITY, INFINITY, 2}, {INFINITY, INFINITY, 11, INFINITY}, {3, 1, INFINITY, INFINITY}}}
};
//--------------------------------------------------------------------------
// the graph itself: G
static pnode G;
static double matrix[MAXNODES][MAXNODES];
//--------------------------------------------------------------------------
void in(char* name)
{
	printf("\nTesting %s\n",name);
}
void init()
{
	G = NULL;
	for(int i=0;i<MAXNODES;i++)
		for(int k=0;k<MAXNODES;k++)
			matrix[i][k]=INFINITY;
}
void teardown()
{
	while(G)
		G = rem_node(G, G->name);
}
void print_verdict(bool cond, int test_no)
{
	if(cond)
	{
		printf(BOLDGREEN "%2d " RESET, test_no+1);
	}
	else
	{
		printf(BOLDRED "%2d " RESET, test_no+1);
	}
	if((test_no+1)%10==0)puts("");
}
float test_is_empty()
{
	in("is_empty");
	bool is_ok = false;
	float points = 0.0;
	for(int i=0;i<NEMPTY;i++)
	{
		init();
		for(int k=0;k<empty_t[i].size;k++)		// adding nodes
			G = add_node(G, empty_t[i].adds[k]);
		is_ok = is_empty(G)==empty_t[i].empty;
		print_verdict(is_ok,i);	// checking empty
		if(is_ok) points += 1.0/(float)NEMPTY;
		teardown();
	}
	return points;
}
float test_add_node()
{
	in("add_node");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NADD;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<add_t[i].size;k++)			// adding nodes
			G = add_node(G, add_t[i].adds[k]);
		for(int k=0;k<add_t[i].size;k++)			// checking that nodes
			if(!get_node(G, add_t[i].adds[k]))		// are in graph
				is_ok = false;
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NADD;
		teardown();
	}
	return points;
}
float test_delete_node()
{
	in("delete_node");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NDEL;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<del_t[i].size_add;k++)		// adding nodes
			G = add_node(G, del_t[i].adds[k]);
		G = rem_node(G, del_t[i].del);				// deleting node
		for(int k=0;k<del_t[i].del_size;k++)		// checking that nodes
			if(!get_node(G, del_t[i].remain[k]))	// are in graph
				is_ok = false;
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NDEL;
		teardown();
	}
	return points;
}
float test_find_node()
{
	in("find_node");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NFIND;i++)
	{
		init();
		for(int k=0;k<find_t[i].size;k++)		// adding nodes
			G = add_node(G, find_t[i].adds[k]);
		is_ok = find_node(G, find_t[i].find) == find_t[i].exists;
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NFIND;
		teardown();
	}
	return points;
}
float test_node_cardinality()
{
	in("node_cardinality");
	float points = 0.0;
	bool is_ok;
	for(int i=0;i<NADD;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<add_t[i].size;k++)			// adding nodes
			G = add_node(G, add_t[i].adds[k]);
		if(node_cardinality(G)!=add_t[i].size)
			is_ok = false;
		print_verdict(is_ok,i);
		teardown();
		if(is_ok)
			points += 1.0/(float)NADD;
	}
	return points;
}
float test_add_edge()
{
	in("add_edge");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NEDGE;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<add_edge_t[i].size_add;k++)			// adding nodes
			G = add_node(G, add_edge_t[i].adds[k]);
		for(int k=0;k<add_edge_t[i].size_edge;k++)			// adding edges
		{
			an_edge tmp = add_edge_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		for(int k=0;k<add_edge_t[i].size_act;k++)			// checking that edges
		{
			an_edge tmp = add_edge_t[i].act_edges[k];
			if(!find_edge(G, tmp.from, tmp.to))		// are in graph
				is_ok = false;
		}
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NEDGE;
		teardown();
	}
	return points;
}
float test_upd_edge()
{
	in("upd_edge");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NUPED;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<upd_edge_t[i].size_add;k++)			// adding nodes
			G = add_node(G, upd_edge_t[i].adds[k]);
		for(int k=0;k<upd_edge_t[i].size_edge;k++)			// adding edges
		{
			an_edge tmp = upd_edge_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		for(int k=0;k<upd_edge_t[i].size_act;k++)			// checking that edges
		{
			an_edge tmp = upd_edge_t[i].act_edges[k];
			if(!find_edge(G, tmp.from, tmp.to))				// are in graph
				is_ok = false;
		}
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NUPED;
		teardown();
	}
	return points;
}
float test_rem_edge()
{
	in("rem_edge");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NREMED;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<rem_edge_t[i].size_add;k++)		// adding nodes
			G = add_node(G, rem_edge_t[i].adds[k]);
		for(int k=0;k<rem_edge_t[i].size_edge;k++)		// adding edges
		{
			an_edge tmp = rem_edge_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		for(int k=0;k<rem_edge_t[i].size_rem;k++)		// removing edges
		{
			edge_id tmp = rem_edge_t[i].rem_edges[k];
			rem_edge(G, tmp.from, tmp.to);
		}
		for(int k=0;k<rem_edge_t[i].size_act;k++)		// checking that edges
		{												// are in graph
			an_edge tmp = rem_edge_t[i].act_edges[k];
			if(!find_edge(G, tmp.from, tmp.to))
				is_ok = false;
		}
		for(int k=0;k<rem_edge_t[i].size_rem;k++)		// checking that edges
		{												// are removed from graph
			edge_id tmp = rem_edge_t[i].rem_edges[k];
			if(find_edge(G, tmp.from, tmp.to))
				is_ok = false;
		}
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NREMED;
		teardown();
	}
	return points;
}
float test_rem_edges()
{
	in("rem_edges");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NREMEDS;i++)
	{
		init();
		is_ok = true;
		for(int k = 0; k < rem_edge_t[i].size_add; k++)		// adding nodes
			G = add_node(G, rem_edge_t[i].adds[k]);
		for(int k = 0; k < rem_edge_t[i].size_edge; k++)		// adding edges
		{
			an_edge tmp = rem_edge_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		for(int k = 0; k < rem_edge_t[i].size_rem; k++)		// removing edges
		{
			edge_id tmp = rem_edge_t[i].rem_edges[k];
			rem_edge(G, tmp.from, tmp.to);
		}
		for(int k = 0; k < rem_edge_t[i].size_act; k++)		// checking that edges
		{												// are in graph
			an_edge tmp = rem_edge_t[i].act_edges[k];
			if(!find_edge(G, tmp.from, tmp.to))
				is_ok = false;
		}
		for(int k = 0;k < rem_edge_t[i].size_rem; k++)		// checking that edges
		{												// are removed from graph
			edge_id tmp = rem_edge_t[i].rem_edges[k];
			if(find_edge(G, tmp.from, tmp.to))
				is_ok = false;
		}
		for(int k = 0; k < rem_edge_t[i].size_add; k++)
			if(!find_node(G, rem_edge_t[i].adds[k]))
				is_ok = false;
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NREMEDS;
		teardown();
	}
	return points;
}
float test_find_edge()
{
	in("find_edge");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NFINDE;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<find_edge_t[i].size_add;k++)			// adding nodes
			G = add_node(G, find_edge_t[i].adds[k]);
		for(int k=0;k<find_edge_t[i].size_edge;k++)			// adding edges
		{
			an_edge tmp = find_edge_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		an_edge tmp = find_edge_t[i].act_edges[0];
		is_ok = find_edge(G,tmp.from, tmp.to)==find_edge_t[i].exists;
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NFINDE;
		teardown();
	}
	return points;
}
float test_edge_cardinality()
{
	in("edge_cardinality");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NCARDE;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<edge_card_t[i].size_add;k++)			// adding nodes
			G = add_node(G, edge_card_t[i].adds[k]);
		for(int k=0;k<edge_card_t[i].size_edge;k++)			// adding edges
		{
			an_edge tmp = edge_card_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		is_ok = edge_cardinality(G)==edge_card_t[i].card;
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NCARDE;
		teardown();
	}
	return points;
}
float test_self_loops()
{
	in("self_loops");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NLOOP;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<self_loop_t[i].size_add;k++)			// adding nodes
			G = add_node(G, self_loop_t[i].adds[k]);
		for(int k=0;k<self_loop_t[i].size_edge;k++)			// adding edges
		{
			an_edge tmp = self_loop_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		is_ok = self_loops(G)==self_loop_t[i].card;
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NLOOP;
		teardown();
	}
	return points;
}
float test_adjacency_matrix()
{
	in("adjacency_matrix");
	bool is_ok;
	float points = 0.0;
	for(int i=0;i<NMAT;i++)
	{
		init();
		is_ok = true;
		for(int k=0;k<list_matrix_t[i].size_add;k++)			// adding nodes
			G = add_node(G, list_matrix_t[i].adds[k]);
		for(int k=0;k<list_matrix_t[i].size_edge;k++)			// adding edges
		{
			an_edge tmp = list_matrix_t[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		list_to_matrix(G,matrix);
		for(int k=0;k<list_matrix_t[i].size_add;k++)
			for(int m=0;m<list_matrix_t[i].size_add;m++)
				if(list_matrix_t[i].matrix[k][m] != matrix[k][m])
				{
		 			is_ok = false;
				}
		print_verdict(is_ok,i);
		if(is_ok) points += 1.0/(float)NMAT;
		teardown();
	}
	return points;
}
float perform_test(test_func tf)
{
	float part = tf();
	if(part>=0.5)
	{
		printf(BOLDGREEN);
		printf("\n\t\t\t\tOK!");
	}
	else
	{
		printf(BOLDRED);
		printf("\n\t\t\t\tNOT OK!");
		part = 0;
	}
	printf(RESET);
	return part;
}
int main()
{
	float section = 0.0, total = 0.0;
	in("Adjacency List\n----------------------");
	section += perform_test(test_is_empty);
	section += perform_test(test_add_node);
	section += perform_test(test_delete_node);
	section += perform_test(test_find_node);
	section += perform_test(test_node_cardinality);
	if(section < 4)
		total = 0.0;
	else
		total += section / 5;
	section = 0.0;
	section += perform_test(test_add_edge);
	section += perform_test(test_upd_edge);
	section += perform_test(test_rem_edge);
	section += perform_test(test_rem_edges);
	section += perform_test(test_find_edge);
	section += perform_test(test_edge_cardinality);
	section += perform_test(test_self_loops);
	section += perform_test(test_adjacency_matrix);
	if(section <= 6)
		total += 0.0;
	else
		total += section / 8;
	printf("\n\t\t\t\t%.1fp\n", total*(1.25));
}
