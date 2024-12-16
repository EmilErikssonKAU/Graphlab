#include "algorithm.h"
// queue - defines a queue as a pointer to an array of pointers to nodes
typedef pnode *queue;
// local prototypes
void init_single_source(pnode G, char s);
void relax(pnode u, pnode v, int w);
int Q_insert(queue Q, pnode u, int index);
int Q_is_empty(queue Q, int size);
pnode Q_extract_min(queue Q, int size);
bool Q_exists(queue Q, int qsize, char name);
int name_to_pos(pnode G, char c);
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES]);
//--------------------------------------------------------------------------
// init single source, relax and min are to be used by algorithms
//--------------------------------------------------------------------------
void init_single_source(pnode G, char s)
{
	for (pnode node = G; !is_empty(node); node = get_next(node)) {
		if (get_name(node) == s) // start node
			set_d(node, 0);
		else
			set_d(node, INFINITY);
		set_pi(node, '-');
	}
}
void relax(pnode u, pnode v, int w)
{
	if (get_d(v) > (get_d(u) + w)) {
		set_d(v, get_d(u) + w);
		set_pi(v, get_name(u));
	}
}
double min(double a, double b)
{
	return a < b ? a : b;
}
//--------------------------------------------------------------------------
// Q functions - used by other algorithms
//--------------------------------------------------------------------------
int Q_insert(queue Q, pnode u, int index)
{
	// TODO
	return 0;
}
int Q_is_empty(queue Q, int size)
{
	// TODO
	return true;
}
pnode Q_extract_min(queue Q, int size)
{
	// TODO
	return NULL;
}
bool Q_exists(queue Q, int qsize, char name)
{
	// TODO
	return false;
}
//--------------------------------------------------------------------------
// Dijkstra's algorithm, single source shortest path tree generator
// a -> b(1) -> c(5)
// b -> c(2)           --> d: [  0,   1,   3]
// c                       e: [  -,   a,   b]
//--------------------------------------------------------------------------
void dijkstra(pnode G, char s, double *d, char *e)
{
	// TODO
}
//--------------------------------------------------------------------------
// Prim's algorithm - Minimum Spanning Tree generator
// start_node: a
// a -> b(1) -> c(5)
// b -> c(2)           --> d: [inf,   1,   2]
// c                       e: [  -,   a,   b]
//--------------------------------------------------------------------------
void prim(pnode G, char start_node, double *d, char *e)
{
	// TODO
}

//--------------------------------------------------------------------------
// Floyd's algorithm: returns matrix of distances
// a -> b(1)
// |                   |0  |1  |3  |
// b -> c(2)    -->    |INF|0  |2  |
// |                   |INF|INF|0  |
// c
//--------------------------------------------------------------------------
void floyd(pnode G, double W[MAXNODES][MAXNODES])
{
	// TODO
}
//--------------------------------------------------------------------------
// Warshall's algorithm: returns matrix of closures, i.e. if paths exists
// a -> b(1)
// |                   |T  |T  |T  |
// b -> c(2)    -->    |F  |T  |T  |
// |                   |F  |F  |T  |
// c
//--------------------------------------------------------------------------
void warshall(pnode G, double W[MAXNODES][MAXNODES])
{
	// TODO
}
