#include "algorithm.h"
// queue - defines a queue as a pointer to an array of pointers to nodes
typedef pnode* queue;

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


// u: prev node
// v: new node
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

double max(double a, double b)
{
	return a > b ? a : b;
}

//--------------------------------------------------------------------------
// Q functions - used by other algorithms
//--------------------------------------------------------------------------
int Q_insert(queue Q, pnode u, int index)
{
	Q[index] = u;
	return index+1;
}

int Q_is_empty(queue Q, int size)
{
	return size==0;
}

pnode Q_extract_min(queue Q, int size)
{
	double min = INFINITY;
	pnode best = NULL;
	int index = -1;
	for(int i = 0;i < size; i++)
		if(Q[i]->d < min)
		{
			min = Q[i]->d;
			best = Q[i];
			index = i;
		}	
	// ta bort nodreferensen ur kön
	if(index!=-1)
	{
		for(int i = index ; i < size-1 ; i++)
			Q[i] = Q[i+1];
	}
	return best;
}

bool Q_exists(queue Q, int qsize, char name)
{
	for(int i=0;i<qsize;i++)
	{
		if (Q[i] -> name == name)
		{
			return true;
		}
	}
	return false;
}


//--------------------------------------------------------------------------
// Other helper functions
//--------------------------------------------------------------------------

queue create_Q(int qsize){
	queue Q = malloc(sizeof(queue)*qsize);
	return Q;

}

void fill_Q(queue Q, pnode G, int qsize){
	pnode node_iter = G;
	for(int i=0; i<qsize; i++){
		Q_insert(Q,node_iter,i);
		node_iter = get_next(node_iter);
	}
}


void adj_list_to_adj_matrix (pnode G, double W[MAXNODES][MAXNODES]){
	int number_nodes = node_cardinality(G);

	// fill matrix with distance inf or 0
	for(int i=0; i<number_nodes; i++){
		for(int j=0; j<number_nodes; j++){
			W[i][j] = i==j ? 0 : INFINITY;
		}
	}

	// insert distance not inf or 0
	pnode node_iter = G;
	for(int i=0; i<number_nodes; i++){
		int number_edges = edge_cardinality(node_iter);
		pedge edge_iter = get_edges(node_iter);

		for(int j=0; j<number_edges; j++){
			int weight = get_weight(edge_iter);
			int node_pos = name_to_pos(G,edge_iter->to);
			W[i][node_pos] = weight;
			edge_iter = get_next_edge(edge_iter);
		}
		node_iter = get_next(node_iter);
	}
}

//--------------------------------------------------------------------------
// Dijkstra's algorithm, single source shortest path tree generator
// a -> b(1) -> c(5)
// b -> c(2)           --> d: [  0,   1,   3]
// c                       e: [  -,   a,   b]
//--------------------------------------------------------------------------
void dijkstra(pnode G, char s, double *d, char *e)
{
	// initalize distance attributes
	init_single_source(G,s);

	// start-index
	int array_index=0;

	// Calculate qsize
	int qsize = node_cardinality(G);

	// Create and fill queue
	queue Q = create_Q(qsize);
	fill_Q(Q,G,qsize);

	while(!Q_is_empty(Q,qsize)){
		// get minimium distance node
		pnode min_d_node = Q_extract_min(Q,qsize);
		
		// insert into arrays
		d[array_index] = get_d(min_d_node);
		e[array_index] = get_name(min_d_node) == s ? '-' : get_name(min_d_node);
		array_index++;

		for(pedge edg = get_edges(min_d_node); edg < edge_cardinality(min_d_node); edg=get_next_edge(edg)){
			pnode adj_node = get_node(G, edg->to);
			relax(min_d_node, adj_node, get_weight(edg));
		}
		qsize--;
	}
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
	// initalize distance attributes
	init_single_source(G,start_node);

	// initialize arrays
	int array_index=0;
	d[array_index] = INFINITY;
	e[array_index] = '-';

	// Calculate qsize
	int qsize = node_cardinality(G);

	// Create and fill queue
	queue Q = create_Q(qsize);
	fill_Q(Q,G,qsize);

	// Loop through queue
	while(!Q_is_empty(Q,qsize)){
		// get minimium distance node
		pnode min_d_node = Q_extract_min(Q,qsize);

		// insert into arrays
		array_index++;
		e[array_index] = get_name(min_d_node);
		d[array_index] = get_d(min_d_node);

		for(pedge edg = get_edges(min_d_node); edg < edge_cardinality(min_d_node); edg=get_next_edge(edg)){
			pnode adj_node = get_node(G, edg->to);
			if(Q_exists(Q,qsize,get_name(adj_node)) && get_d(min_d_node)+get_weight(edg) < get_d(adj_node)){
				set_d(adj_node, get_d(min_d_node)+get_weight(edg));
			}
		}
		qsize--;
	}
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
	adj_list_to_adj_matrix(G,W);
	int number_nodes = node_cardinality(G);

	for(int k=0; k<number_nodes; k++){
		for(int i=0; i<number_nodes; i++){
			for(int j=0; j<number_nodes; j++){
				W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
			}
		}
	}

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
	int number_nodes = node_cardinality(G);
	list_to_matrix(G,W);

	for(int k=0; k<number_nodes; k++){
		for(int i=0; i<number_nodes; i++){
			for(int j=0; j<number_nodes; j++){
				W[i][j] = max(W[i][j], W[i][k] + W[k][j]);
			}
		}
	}
}
