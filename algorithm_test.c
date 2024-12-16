#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "adjlist.h"
#include "algorithm.h"
#define NDIJK 27
#define NPRIM 35
#define NFLOY 18
#define RESET   	"\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
typedef float (*test_func)();
typedef struct an_edge{
	char from;
	char to;
	double weight;
}an_edge;
typedef struct dijkstra_test{
	int size_node;
	char adds[MAXNODES];
	int size_edge;
	an_edge add_edges[MAXNODES*MAXNODES];
	char start_node;
	double d[MAXNODES];
	char pi[MAXNODES];
}dijkstra_test;
typedef struct flwa_test{
	int size_node;
	char adds[MAXNODES];
	int size_edge;
	an_edge add_edges[MAXNODES*MAXNODES];
	double table[MAXNODES][MAXNODES];
}flwa_test;
dijkstra_test dtests[] = {
	{2, {'a', 'b'}, 1, {{'a', 'b', 1}}, 'a', { 0, 1 }, { '-', 'a' }},
    {2, {'a', 'b'}, 1, {{'b', 'a', 1}}, 'b', { 1, 0 }, { 'b', '-' }},
    {3, {'a', 'b', 'c'}, 2, {{'a', 'b', 1}, {'b', 'c', 2}}, 'a', { 0, 1, 3 }, { '-', 'a', 'b' }},
    {4, {'a', 'b', 'c', 'd'},5,  {{'b', 'a', 4}, {'c', 'a', 2}, {'c', 'b', 1}, {'d', 'b', 3}, {'d', 'c', 1}}, 'd', { 3, 2, 1, 0 }, { 'c', 'c', 'd', '-' }},
    {4, {'a', 'b', 'c', 'd'}, 6, {{'b', 'a', 6}, {'b', 'c', 2}, {'b', 'd', 4}, {'c', 'a', 3}, {'c', 'd', 1}, {'d', 'a', 1}}, 'b', { 4, 0, 2, 3 }, { 'd', '-', 'b', 'c' }},
    {5, {'a', 'b', 'c', 'd', 'e'},7, {{'a', 'b', 2}, {'a', 'c', 5}, {'b', 'c', 1}, {'b', 'd', 3}, {'c', 'd', 1}, {'c', 'e', 10}, {'d', 'e', 7}}, 'a', { 0, 2, 3, 4, 11 }, { '-', 'a', 'b', 'c', 'd' }},
    {5, {'a', 'b', 'c', 'd', 'e'},7, {{'a', 'b', 3}, {'a', 'c', 6}, {'a', 'd', 9}, {'a', 'e', 12}, {'b', 'c', 1}, {'c', 'd', 2}, {'d', 'e', 3}}, 'a', { 0, 3, 4, 6, 9 }, { '-', 'a', 'b', 'c', 'd' }},
    {5, {'a', 'b', 'c', 'd', 'e'},7, {{'a', 'b', 3}, {'a', 'c', 6}, {'a', 'd', 9}, {'a', 'e', 12}, {'b', 'c', 4}, {'c', 'd', 1}, {'d', 'e', 12}}, 'a', { 0, 3, 6, 7, 12 }, { '-', 'a', 'a', 'c', 'a' }},
    {5, {'a', 'b', 'c', 'd', 'e'},9, {{'a', 'b', 1}, {'b', 'a', 1}, {'b', 'd', 1}, {'c', 'a', 5}, {'c', 'b', 3}, {'c', 'd', 4}, {'d', 'c', 2}, {'d', 'b', 8}, {'e', 'd', 10}}, 'e', { 16, 15, 12, 10, 0 }, { 'b', 'c', 'd', 'e', '-' }},
    {6, {'a', 'b', 'c', 'd', 'e', 'f'}, 10, {{'b', 'd', 7}, {'b', 'e', 5}, {'b', 'f', 2}, {'c', 'a', 2}, {'c', 'd', 6}, {'d', 'a', 2}, {'e', 'c', 1}, {'f', 'c', 5}, {'f', 'd', 6}, {'f', 'e', 6}}, 'b', { 8, 0, 6, 7, 5, 2 }, { 'c', '-', 'e', 'b', 'b', 'b' }},
    {6, {'a', 'b', 'c', 'd', 'e', 'f'}, 9, {{'a', 'd', 1}, {'a', 'f', 1}, {'b', 'd', 1}, {'c', 'e', 1}, {'c', 'f', 4}, {'d', 'a', 2}, {'e', 'a', 3}, {'e', 'b', 1}, {'f', 'a', 1}}, 'c', { 4, 2, 0, 3, 1, 4 }, { 'e', 'e', '-', 'b', 'c', 'c' }},
	// Undirected graph (1/4)
	{4, {'a', 'b', 'c', 'd'},12,  {{'a', 'b', 2}, {'a', 'c', 5}, {'a', 'd', 3}, {'b', 'a', 2}, {'b', 'c', 5}, {'b', 'd', 3}, {'c', 'a', 5}, {'c', 'b', 5}, {'c', 'd', 1}, {'d', 'a', 3}, {'d', 'b', 3}, {'d', 'c', 1}},'a',  {0, 2, 4, 3}, {'-','a','d','a'}},
	{4,{'a', 'b', 'c', 'd'}, 12,  {{'a', 'b', 2}, {'a', 'c', 5}, {'a', 'd', 3}, {'b', 'a', 2}, {'b', 'c', 5}, {'b', 'd', 3}, {'c', 'a', 5}, {'c', 'b', 5}, {'c', 'd', 1}, {'d', 'a', 3}, {'d', 'b', 3}, {'d', 'c', 1}}, 'b', {2, 0, 4, 3},    {'b','-','d','b'}},
	{4,{'a', 'b', 'c', 'd'},12, {{'a', 'b', 2}, {'a', 'c', 5}, {'a', 'd', 3}, {'b', 'a', 2}, {'b', 'c', 5}, {'b', 'd', 3}, {'c', 'a', 5}, {'c', 'b', 5}, {'c', 'd', 1}, {'d', 'a', 3}, {'d', 'b', 3}, {'d', 'c', 1}},'d', {3, 3, 1, 0}, {'d','d','d', '-'}},
	// Undirected graph (2/4)
	{5,{'a', 'b', 'c', 'd', 'e'},12, {{'a', 'b', 2}, {'a', 'c', 1}, {'b', 'a', 2}, {'b', 'c', 4}, {'c', 'a', 1}, {'c', 'b', 4}, {'c', 'd', 6}, {'c', 'e', 5}, {'d', 'c', 6}, {'d', 'e', 3}, {'e', 'c', 5}, {'e', 'd', 3}},'a',{0, 2, 1, 7, 6, 0},  {'-','a','a','c','c'}},
	{ 5, {'a', 'b', 'c', 'd', 'e'}, 12, {{'a', 'b', 2}, {'a', 'c', 1}, {'b', 'a', 2}, {'b', 'c', 4}, {'c', 'a', 1}, {'c', 'b', 4}, {'c', 'd', 6}, {'c', 'e', 5}, {'d', 'c', 6}, {'d', 'e', 3}, {'e', 'c', 5}, {'e', 'd', 3}},'b', {2, 0, 3, 9, 8,0}, {'b','-','a','c','c'}},
	{5, {'a', 'b', 'c', 'd', 'e'}, 12, {{'a', 'b', 2}, {'a', 'c', 1}, {'b', 'a', 2}, {'b', 'c', 4}, {'c', 'a', 1}, {'c', 'b', 4}, {'c', 'd', 6}, {'c', 'e', 5}, {'d', 'c', 6}, {'d', 'e', 3}, {'e', 'c', 5}, {'e', 'd', 3}}, 'c', {1, 3, 0, 6, 5, 0}, {'c','a','-','c','c'}},
	{5, {'a', 'b', 'c', 'd', 'e'}, 12, {{'a', 'b', 2}, {'a', 'c', 1}, {'b', 'a', 2}, {'b', 'c', 4}, {'c', 'a', 1}, {'c', 'b', 4}, {'c', 'd', 6}, {'c', 'e', 5}, {'d', 'c', 6}, {'d', 'e', 3}, {'e', 'c', 5}, {'e', 'd', 3}}, 'd', {7, 9, 6, 0, 3, 0}, {'c','a','d','-','d'}},
	{ 5,{'a', 'b', 'c', 'd', 'e'}, 12, {{'a', 'b', 2}, {'a', 'c', 1}, {'b', 'a', 2}, {'b', 'c', 4}, {'c', 'a', 1}, {'c', 'b', 4}, {'c', 'd', 6}, {'c', 'e', 5}, {'d', 'c', 6}, {'d', 'e', 3}, {'e', 'c', 5}, {'e', 'd', 3}},'e', {6, 8, 5, 3, 0, 0}, {'c','a','e','e','-'}},
	// Undirected graph (3/4)
	{5, {'a', 'b', 'c', 'd', 'e'}, 16, {{'a', 'b', 4}, {'a', 'c', 5}, {'a', 'd', 1}, {'b', 'a', 4}, {'b', 'c', 2}, {'b', 'd', 1}, {'c', 'a', 5}, {'c', 'b', 2}, {'c', 'd', 5}, {'c', 'e', 4}, {'d', 'a', 1}, {'d', 'b', 1}, {'d', 'c', 5}, {'d','e', 2}, {'e', 'c', 4}, {'e', 'd', 2}}, 'a', {0, 2, 4, 1, 3, 0},{'-','d','b','a','d'}},
	{5,{'a', 'b', 'c', 'd', 'e'}, 16, {{'a', 'b', 4}, {'a', 'c', 5}, {'a', 'd', 1}, {'b', 'a', 4}, {'b', 'c', 2}, {'b', 'd', 1}, {'c', 'a', 5}, {'c', 'b', 2}, {'c', 'd', 5}, {'c', 'e', 4}, {'d', 'a', 1}, {'d', 'b', 1}, {'d', 'c', 5}, {'d', 'e', 2}, {'e', 'c', 4}, {'e', 'd', 2}},'b',{2, 0, 2, 1, 3, 0}, {'d','-','b','b','d'}},
	{5, {'a', 'b', 'c', 'd', 'e'}, 16, {{'a', 'b', 4}, {'a', 'c', 5}, {'a', 'd', 1}, {'b', 'a', 4}, {'b', 'c', 2}, {'b', 'd', 1}, {'c', 'a', 5}, {'c', 'b', 2}, {'c', 'd', 5}, {'c', 'e', 4}, {'d', 'a', 1}, {'d', 'b', 1}, {'d', 'c', 5}, {'d', 'e', 2}, {'e', 'c', 4}, {'e', 'd', 2}},'d', {1, 1, 3, 0, 2, 0}, {'d','d','b','-','d'}},
	{5,{'a', 'b', 'c', 'd', 'e'}, 16, {{'a', 'b', 4}, {'a', 'c', 5}, {'a', 'd', 1}, {'b', 'a', 4}, {'b', 'c', 2}, {'b', 'd', 1}, {'c', 'a', 5}, {'c', 'b', 2}, {'c', 'd', 5}, {'c', 'e', 4}, {'d', 'a', 1}, {'d', 'b', 1}, {'d', 'c', 5}, {'d', 'e', 2}, {'e', 'c', 4}, {'e', 'd', 2}}, 'e', {3, 3, 4, 2, 0, 0}, {'d','d','e','e','-'}},
	// Undirected graph (4/4)
	{6, {'a', 'b', 'c', 'd', 'e', 'f'}, 22, {{'a', 'b', 9}, {'a', 'c', 13}, {'a', 'd', 7}, {'b', 'a', 9}, {'b', 'c', 2}, {'b', 'e', 3}, {'b', 'f', 5}, {'c', 'a', 13}, {'c', 'b', 2}, {'c', 'd', 1}, {'c', 'e', 5}, {'d', 'a', 7}, {'d', 'c', 1}, {'d', 'e', 9}, {'d', 'f', 3}, {'e', 'b', 3}, {'e', 'c', 5}, {'e', 'd', 9}, {'e', 'f', 1}, {'f', 'b', 5}, {'f', 'd', 3}, {'f', 'e', 1}}, 'a', {0, 9, 8, 7, 11, 10}, {'-','a','d','a','f','d'}},
	{ 6, {'a', 'b', 'c', 'd', 'e', 'f'}, 22, {{'a', 'b', 9}, {'a', 'c', 13}, {'a', 'd', 7}, {'b', 'a', 9}, {'b', 'c', 2}, {'b', 'e', 3}, {'b', 'f', 5}, {'c', 'a', 13}, {'c', 'b', 2}, {'c', 'd', 1}, {'c', 'e', 5}, {'d', 'a', 7}, {'d', 'c', 1}, {'d', 'e', 9}, {'d', 'f', 3}, {'e', 'b', 3}, {'e', 'c', 5}, {'e', 'd', 9}, {'e', 'f', 1}, {'f', 'b', 5}, {'f', 'd', 3}, {'f', 'e', 1}},'b', {9, 0, 2, 3, 3, 4},  {'b','-','b','c','b','e'}},
	{6, {'a', 'b', 'c', 'd', 'e', 'f'}, 22, {{'a', 'b', 9}, {'a', 'c', 13}, {'a', 'd', 7}, {'b', 'a', 9}, {'b', 'c', 2}, {'b', 'e', 3}, {'b', 'f', 5}, {'c', 'a', 13}, {'c', 'b', 2}, {'c', 'd', 1}, {'c', 'e', 5}, {'d', 'a', 7}, {'d', 'c', 1}, {'d', 'e', 9}, {'d', 'f', 3}, {'e', 'b', 3}, {'e', 'c', 5}, {'e', 'd', 9}, {'e', 'f', 1}, {'f', 'b', 5}, {'f', 'd', 3}, {'f', 'e', 1}}, 'd', {7, 3, 1, 0, 4, 3}, {'d','c','d','-','f','d'}},
	{6, {'a', 'b', 'c', 'd', 'e', 'f'}, 22, {{'a', 'b', 9}, {'a', 'c', 13}, {'a', 'd', 7}, {'b', 'a', 9}, {'b', 'c', 2}, {'b', 'e', 3}, {'b', 'f', 5}, {'c', 'a', 13}, {'c', 'b', 2}, {'c', 'd', 1}, {'c', 'e', 5}, {'d', 'a', 7}, {'d', 'c', 1}, {'d', 'e', 9}, {'d', 'f', 3}, {'e', 'b', 3}, {'e', 'c', 5}, {'e', 'd', 9}, {'e', 'f', 1}, {'f', 'b', 5}, {'f', 'd', 3}, {'f', 'e', 1}}, 'f', {10, 4, 4, 3, 1, 0}, {'d','e','d','f','f','-'}},
};
dijkstra_test ptests[] = {
	// Basic
	{2, {'a','b'}, 1, {{'a','b',1}}, 'a', {INFINITY,1}, {'-','a'}},
	{2, {'a','b'}, 2, {{'a','b',1},{'a','a',1}}, 'a', {INFINITY,1}, {'-','a'}},
	{3, {'a','b','c'}, 2, {{'a','b',1},{'b','c',2}}, 'a', {INFINITY,1,2}, {'-','a','b'}},
	{3, {'a','b','c'}, 2, {{'a','b',1},{'b','c',2}}, 'b', {1,INFINITY,2}, {'b','-','b'}},
	{3, {'a','b','c'}, 2, {{'a','b',1},{'b','c',2}}, 'c', {1,2,INFINITY}, {'b','c','-'}},
	// Graph 1
	{4, {'a','b','c','d'},5,  {{'a','b',2},{'a','c',4},{'b','c',1},{'b','d',3},{'c','d',5}}, 'a', {INFINITY,2,1,3}, {'-','a','b','b'}},
	{4, {'a','b','c','d'}, 5, {{'a','b',2},{'a','c',4},{'b','c',1},{'b','d',3},{'c','d',5}}, 'b', {2,INFINITY,1,3}, {'b','-','b','b'}},
	{4, {'a','b','c','d'}, 5, {{'a','b',2},{'a','c',4},{'b','c',1},{'b','d',3},{'c','d',5}}, 'c', {2,1,INFINITY,3}, {'b','c','-','b'}},
	{4, {'a','b','c','d'}, 5, {{'a','b',2},{'a','c',4},{'b','c',1},{'b','d',3},{'c','d',5}}, 'd', {2,3,1,INFINITY}, {'b','d','b','-'}},
	// Graph 2
	{4, {'a','b','c','d'}, 6, {{'a','b',3},{'a','c',2},{'a','d',7},{'b','c',5},{'b','d',8},{'c','d',9}}, 'a', {INFINITY,3,2,7}, {'-','a','a','a'}},
	{4, {'a','b','c','d'},6, {{'a','b',3},{'a','c',2},{'a','d',7},{'b','c',5},{'b','d',8},{'c','d',9}}, 'b', {3,INFINITY,2,7}, {'b','-','a','a'}},
	{4, {'a','b','c','d'},6, {{'a','b',3},{'a','c',2},{'a','d',7},{'b','c',5},{'b','d',8},{'c','d',9}}, 'c', {2,3,INFINITY,7}, {'c','a','-','a'}},
	{4, {'a','b','c','d'},6, {{'a','b',3},{'a','c',2},{'a','d',7},{'b','c',5},{'b','d',8},{'c','d',9}}, 'd', {7,3,2,INFINITY}, {'d','a','a','-'}},
	// Graph 3
	{5, {'a','b','c','d','e'},7, {{'a','b',3},{'a','c',1},{'b','c',2},{'b','d',1},{'c','d',4},{'c','e',3},{'d','e',2}}, 'a', {INFINITY,2,1,1,2}, {'-','c','a','b','d'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',3},{'a','c',1},{'b','c',2},{'b','d',1},{'c','d',4},{'c','e',3},{'d','e',2}}, 'b', {1,INFINITY,2,1,2}, {'c','-','b','b','d'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',3},{'a','c',1},{'b','c',2},{'b','d',1},{'c','d',4},{'c','e',3},{'d','e',2}}, 'c', {1,2,INFINITY,1,2}, {'c','c','-','b','d'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',3},{'a','c',1},{'b','c',2},{'b','d',1},{'c','d',4},{'c','e',3},{'d','e',2}}, 'd', {1,1,2,INFINITY,2}, {'c','d','b','-','d'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',3},{'a','c',1},{'b','c',2},{'b','d',1},{'c','d',4},{'c','e',3},{'d','e',2}}, 'e', {1,1,2,2,INFINITY}, {'c','d','b','e','-'}},
	// Graph 4
	{5, {'a','b','c','d','e'},7, {{'a','b',2},{'a','c',4},{'a','e',3},{'b','c',1},{'c','d',5},{'c','e',4},{'d','e',2}}, 'a', {INFINITY,2,1,2,3}, {'-','a','b','e','a'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',2},{'a','c',4},{'a','e',3},{'b','c',1},{'c','d',5},{'c','e',4},{'d','e',2}}, 'b', {2,INFINITY,1,2,3}, {'b','-','b','e','a'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',2},{'a','c',4},{'a','e',3},{'b','c',1},{'c','d',5},{'c','e',4},{'d','e',2}}, 'c', {2,1,INFINITY,2,3}, {'b','c','-','e','a'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',2},{'a','c',4},{'a','e',3},{'b','c',1},{'c','d',5},{'c','e',4},{'d','e',2}}, 'd', {3,2,1,INFINITY,2}, {'e','a','b','-','d'}},
	{5, {'a','b','c','d','e'},7, {{'a','b',2},{'a','c',4},{'a','e',3},{'b','c',1},{'c','d',5},{'c','e',4},{'d','e',2}}, 'e', {3,2,1,2,INFINITY}, {'e','a','b','e','-'}},
	// Graph 5
	{6, {'a','b','c','d','e','f'}, 10, {{'a','b',2},{'a','c',4},{'a','d',1},{'b','c',1},{'b','f',5},{'c','d',3},{'c','e',4},{'c','f',6},{'d','e',2},{'e','f',7}}, 'a', {INFINITY,2,1,1,2,5}, {'-','a','b','a','d','b'}},
	{6, {'a','b','c','d','e','f'},10, {{'a','b',2},{'a','c',4},{'a','d',1},{'b','c',1},{'b','f',5},{'c','d',3},{'c','e',4},{'c','f',6},{'d','e',2},{'e','f',7}}, 'b', {2,INFINITY,1,1,2,5}, {'b','-','b','a','d','b'}},
	{6, {'a','b','c','d','e','f'},10, {{'a','b',2},{'a','c',4},{'a','d',1},{'b','c',1},{'b','f',5},{'c','d',3},{'c','e',4},{'c','f',6},{'d','e',2},{'e','f',7}}, 'c', {2,1,INFINITY,1,2,5}, {'b','c','-','a','d','b'}},
	{6, {'a','b','c','d','e','f'},10, {{'a','b',2},{'a','c',4},{'a','d',1},{'b','c',1},{'b','f',5},{'c','d',3},{'c','e',4},{'c','f',6},{'d','e',2},{'e','f',7}}, 'd', {1,2,1,INFINITY,2,5}, {'d','a','b','-','d','b'}},
	{6, {'a','b','c','d','e','f'},10, {{'a','b',2},{'a','c',4},{'a','d',1},{'b','c',1},{'b','f',5},{'c','d',3},{'c','e',4},{'c','f',6},{'d','e',2},{'e','f',7}}, 'e', {1,2,1,2,INFINITY,5}, {'d','a','b','e','-','b'}},
	{6, {'a','b','c','d','e','f'},10, {{'a','b',2},{'a','c',4},{'a','d',1},{'b','c',1},{'b','f',5},{'c','d',3},{'c','e',4},{'c','f',6},{'d','e',2},{'e','f',7}}, 'f', {2,5,1,1,2,INFINITY}, {'b','f','b','a','d','-'}},
	// Graph 6
	{6, {'a','b','c','d','e','f'},8, {{'a','b',2},{'a','c',1},{'b','d',5},{'b','e',7},{'c','d',4},{'c','f',13},{'d','e',1},{'e','f',5}}, 'a', {INFINITY,2,1,4,1,5}, {'-','a','a','c','d','e'}},
	{6, {'a','b','c','d','e','f'},8, {{'a','b',2},{'a','c',1},{'b','d',5},{'b','e',7},{'c','d',4},{'c','f',13},{'d','e',1},{'e','f',5}}, 'b', {2,INFINITY,1,4,1,5}, {'b','-','a','c','d','e'}},
	{6, {'a','b','c','d','e','f'},8, {{'a','b',2},{'a','c',1},{'b','d',5},{'b','e',7},{'c','d',4},{'c','f',13},{'d','e',1},{'e','f',5}}, 'c', {1,2,INFINITY,4,1,5}, {'c','a','-','c','d','e'}},
	{6, {'a','b','c','d','e','f'},8, {{'a','b',2},{'a','c',1},{'b','d',5},{'b','e',7},{'c','d',4},{'c','f',13},{'d','e',1},{'e','f',5}}, 'd', {1,2,4,INFINITY,1,5}, {'c','a','d','-','d','e'}},
	{6, {'a','b','c','d','e','f'},8, {{'a','b',2},{'a','c',1},{'b','d',5},{'b','e',7},{'c','d',4},{'c','f',13},{'d','e',1},{'e','f',5}}, 'e', {1,2,4,1,INFINITY,5}, {'c','a','d','e','-','e'}},
	{6, {'a','b','c','d','e','f'},8, {{'a','b',2},{'a','c',1},{'b','d',5},{'b','e',7},{'c','d',4},{'c','f',13},{'d','e',1},{'e','f',5}}, 'f', {1,2,4,1,5,INFINITY}, {'c','a','d','e','f','-'}},
};
flwa_test flwatests[] = {
	// Basic
	{1, {'a'}, 0, {{0}}, {{0}}},
	{2, {'a','b'}, 1, {{'a','b',1}}, { {0,1}, {INFINITY,0} }},
	{2, {'a','b'}, 1, {{'b','a',2}}, { {0,INFINITY}, {2,0} }},
	{2, {'a','b'}, 2, {{'a','b',1},{'b','a',2}}, { {0,1}, {2,0} }},
	{3, {'a','b','c'}, 2, {{'a','b',1}, {'b','c',2}}, { {0,1,3}, {INFINITY,0,2}, {INFINITY,INFINITY,0} }},
	{3, {'a','b','c'}, 3, {{'a','b',1},{'b','c',2},{'c','a',3}}, { {0,1,3}, {5,0,2}, {3,4,0} }},
	{3, {'a','b','c'}, 4, {{'a','b',1},{'b','c',2},{'c','a',3},{'c','b',2}}, { {0,1,3}, {5,0,2}, {3,2,0} }},
	// Directed graph {1/6}
	{4, {'a','b','c','d'}, 5, {{'a','c',2},{'a','d',3},{'b','a',5},{'c','b',1},{'d','b',1}}, { {0,3,2,3}, {5,0,7,8}, {6,1,0,9}, {6,1,8,0} }},
	// Directed graph {2/6}
	{4, {'a','b','c','d'}, 6,  {{'a','b',1},{'a','c',1},{'b','a',1},{'b','c',3},{'c','d',2},{'d','b',2}}, { {0,1,1,3}, {1,0,2,4}, {5,4,0,2}, {3,2,4,0} }},
	// Directed graph {3/6}
	{5, {'a','b','c','d','e'}, 8, {{'a','b',2},{'a','d',4},{'b','c',3},{'c','e',1},{'d','a',2},{'d','c',1},{'e','b',1},{'e','c',2}}, { {0,2,5,4,6}, {INFINITY,0,3,INFINITY,4}, {INFINITY,2,0,INFINITY,1}, {2,3,1,0,2}, {INFINITY,1,2,INFINITY,0}}},
	// Directed graph {4/6}
	{5, {'a','b','c','d','e'}, 8, {{'a','b',2},{'a','c',1},{'b','e',2},{'c','b',2},{'c','d',1},{'d','e',1},{'d','a',3},{'e','a',4}}, { {0,2,1,2,3}, {6,0,7,8,2}, {4,2,0,1,2}, {3,5,4,0,1}, {4,6,5,6,0} }},
	// Directed graph {5/6}
	{6, {'a','b','c','d','e','f'}, 11, {{'a','b',2},{'b','a',2},{'b','d',3},{'c','a',1},{'c','d',2},{'d','c',2},{'d','e',3},{'d','f',1},{'e','b',3},{'e','f',2},{'f','e',2}}, { {0,2,7,5,8,6}, {2,0,5,3,6,4}, {1,3,0,2,5,3}, {3,5,2,0,3,1}, {5,3,8,6,0,2}, {7,5,10,8,2,0} }},
	// Directed graph {6/6}
	{6, {'a','b','c','d','e','f'}, 11, {{'a','b',2},{'a','d',1},{'b','c',3},{'b','e',2},{'c','a',1},{'d','c',3},{'d','f',4},{'e','b',10},{'e','d',1},{'f','e',5},{'f','a',7}}, { {0,2,4,1,4,5}, {4,0,3,3,2,7}, {1,3,0,2,5,6}, {4,6,3,0,8,4}, {5,7,4,1,0,5}, {7,9,9,6,5,0} }},
	// Undirected graph {1/5}
	{4, {'a','b','c','d'}, 12,  {{'a','b',3},{'a','c',5},{'a','d',1},{'b','a',3},{'b','c',1},{'b','d',2},{'c','a',5},{'c','b',1},{'c','d',5},{'d','a',1},{'d','b',2},{'d','c',5}}, { {0,3,4,1}, {3,0,1,2}, {4,1,0,3}, {1,2,3,0} }},
	// Undirected graph {2/5}
	{4, {'a','b','c','d'}, 10, {{'a','b',2},{'a','c',1},{'b','a',2},{'b','c',3},{'b','d',1},{'c','a',1},{'c','b',3},{'c','d',5},{'d','b',1},{'d','c',5}}, { {0,2,1,3}, {2,0,3,1}, {1,3,0,4}, {3,1,4,0} }},
	// Undirected graph {3/5}
	{5, {'a','b','c','d','e'}, 14, {{'a','b',5},{'a','c',2},{'a','d',3},{'b','a',5},{'b','c',3},{'b','e',1},{'c','a',2},{'c','b',3},{'c','e',1},{'d','a',3},{'d','e',6},{'e','b',1},{'e','c',1},{'e','d',6}}, { {0,4,2,3,3,}, {4,0,2,7,1}, {2,2,0,5,1}, {3,7,5,0,6}, {3,1,1,6,0} }},
	// Undirected graph {4/5}
	{7, {'a','b','c','d','e','f','g'}, 20,  {{'a','b',1},{'a','c',7},{'a','d',3},{'b','a',1},{'b','e',1},{'b','g',3},{'c','a',7},{'c','d',3},{'c','f',1},{'d','a',3},{'d','c',3},{'d','f',2},{'e','b',1},{'e','g',1},{'f','c',1},{'f','d',2},{'f','g',1},{'g','b',3},{'g','e',1},{'g','f',1}}, { {0,1,5,3,2,4,3}, {1,0,4,4,1,3,2}, {5,4,0,3,3,1,2}, {3,4,3,0,4,2,3}, {2,1,3,4,0,2,1}, {4,3,1,2,2,0,1}, {3,2,2,3,1,1,0} }},
	// Undirected graph {5/5}
	{6, {'a','b','c','d','e','f'}, 10,  {{'a','b',1},{'a','c',1},{'b','a',1},{'b','c',3},{'c','a',1},{'c','b',3},{'d','e',2},{'d','f',1},{'e','d',2},{'f','d',1}}, { {0,1,1,INFINITY,INFINITY,INFINITY}, {1,0,2,INFINITY,INFINITY,INFINITY}, {1,2,0,INFINITY,INFINITY,INFINITY}, {INFINITY,INFINITY,INFINITY,0,2,1}, {INFINITY,INFINITY,INFINITY,2,0,3}, {INFINITY,INFINITY,INFINITY,1,3,0} }},
};
//---------------------------------------------------------------------
// The graph and matrix
//---------------------------------------------------------------------
static pnode G;
double matrix[MAXNODES][MAXNODES];
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
	while(!is_empty(G))
		G = rem_node(G, G->name);
	//printf("\ntearing down the house\n");
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
float test_dijkstra()
{
	in("Dijkstra");
	bool is_ok;
	float points = 0.0;
	double *d;						// arrays for results
	char *e;
	for(int i=0; i<NDIJK; i++)
	{
		init();
		is_ok = true;
		for(int k = 0; k < dtests[i].size_node; k++)			// adding nodes
			G = add_node(G, dtests[i].adds[k]);
		int n = node_cardinality(G);
		for(int k = 0; k < dtests[i].size_edge; k++)			// adding edges
		{
			an_edge tmp = dtests[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		d = (double*)malloc(n*sizeof(double));
		e = (char*)malloc(n*sizeof(char));
		if(!G)is_ok=false;
		dijkstra(G, dtests[i].start_node, d, e);
		for(int k=0 ; k<n ;k++)
		{
			if(dtests[i].pi[k] != e[k] || dtests[i].d[k] != d[k])
			{
				is_ok = false;

				printf("%.0lf <->%.0lf\n",dtests[i].d[k], d[k]);
			}
		}
		free(d);free(e);
		if(is_ok)points += 1.0/(float)NDIJK;
		print_verdict(is_ok,i);
		teardown();
	}
	return points;

}
float test_prim()
{
	in("Prim");
	bool is_ok;
	float points = 0.0;
	double *d;												// arrays for results
	char *e;
	for(int i = 0; i < NPRIM ; i++)
	{
		init();
		is_ok = true;
		for(int k = 0 ; k < ptests[i].size_node; k++)	// adding nodes
			G = add_node(G, ptests[i].adds[k]);
		for(int k = 0; k < ptests[i].size_edge; k++)	// adding edges
		{
			an_edge tmp = ptests[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
			add_edge(G, tmp.to, tmp.from, tmp.weight);
		}
		d = (double*)malloc(ptests[i].size_node*sizeof(double));
		e = (char*)malloc(ptests[i].size_node*sizeof(char));
		if(!G)is_ok=false;
		prim(G, ptests[i].start_node, d, e);			// running prim
		for(int k = 0; k < node_cardinality(G); k++)	// checking results
			if(ptests[i].pi[k] != e[k] || ptests[i].d[k] != d[k])
				is_ok = false;
		free(d);free(e);
		if(is_ok)points += 1.0/(float)NPRIM;
		print_verdict(is_ok,i);
		teardown();
	}
	return points;
}
float test_floyd()
{
	in("Floyd");
	bool is_ok;
	float points = 0.5;
	double d[MAXNODES][MAXNODES];							// matrix for results
	for(int i = 0; i < NFLOY ; i++)
	{
		init();
		for(int x = 0; x < MAXNODES ; x++)				// initializing
			for(int y = 0; y < MAXNODES ; y++)			// matrix
				d[x][y] = (x!=y)?INFINITY:0;
		is_ok = true;
		for(int k = 0 ; k < flwatests[i].size_node; k++)// adding nodes
			G = add_node(G, flwatests[i].adds[k]);
		for(int k = 0; k < flwatests[i].size_edge; k++)	// adding edges
		{
			an_edge tmp = flwatests[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		if(!G)is_ok=false;
		floyd(G, d);									// running floyd
		for(int k = 0; k < node_cardinality(G); k++)	// checking results
			for(int m = 0; m < node_cardinality(G); m++)
				if(flwatests[i].table[k][m] != d[k][m])
				{
					is_ok = false;
					printf("%.0lf != %.0lf\n", flwatests[i].table[k][m], d[k][m]);
				}
		print_verdict(is_ok,i);
		if(!is_ok)points -= (0.5/(float)NFLOY);
		teardown();
	}
	if(points<0.25)points = 0;
	return points;
}
float test_warshall()
{
	in("Warshall");
	bool is_ok;
	float points = 0.5;
	double d[MAXNODES][MAXNODES];							// matrix for results
	for(int i = 0; i < NFLOY ; i++)
	{
		init();
		for(int x = 0; x < MAXNODES ; x++)
			for(int y = 0; y < MAXNODES ; y++)
				d[x][y] = x!=y?INFINITY:0;
		is_ok = true;
		for(int k = 0 ; k < flwatests[i].size_node; k++)	// adding nodes
			G = add_node(G, flwatests[i].adds[k]);
		for(int k = 0; k < flwatests[i].size_edge; k++)	// adding edges
		{
			an_edge tmp = flwatests[i].add_edges[k];
			add_edge(G, tmp.from, tmp.to, tmp.weight);
		}
		if(!G)is_ok=false;
		warshall(G, d);
		for(int k = 0; k < node_cardinality(G); k++)	// checking results
			for(int m = 0; m < node_cardinality(G); m++)
			{
				bool tmp = flwatests[i].table[k][m]!=INFINITY;
				if(tmp != d[k][m])
				{
					is_ok = false;
					printf("%d != %.0lf\n", tmp, d[k][m]);
				}
			}
		print_verdict(is_ok,i);
		if(!is_ok)points -= (0.5/(float)NFLOY);
		teardown();
	}
	if(points<0.25)points = 0;
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
	float total = 0.0;
	in("Algorithms\n------------------");
	total += perform_test(test_dijkstra);
	total += perform_test(test_prim);
	total += perform_test(test_floyd);
	total += perform_test(test_warshall);
	printf("\n\t\t\t\t%.1fp", total);
	printf("\nCode Quality (manual)\t\t   p\n");
}
