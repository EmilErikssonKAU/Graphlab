#include "adjlist.h"
void dijkstra(pnode G, char s, double *d, char *e);
void prim(pnode G, char start_node, double *d, char *e);
void floyd(pnode G, double W[MAXNODES][MAXNODES]);
void warshall(pnode G, double W[MAXNODES][MAXNODES]);
