#include "adjlist.h"
// local prototypes
pnode create_node(char nname);
pnode node_cons(pnode first, pnode second);
pedge create_edge(char to, double weight);
pedge edge_cons(pedge first, pedge second);
pedge _add_edge(pedge edge, char to, double weight);
pedge _rem_edge(pedge edges, char to);
void remove_all_edges_to(pnode G, char name);
void remove_all_edges_from(pnode G, char name);

// create_node: creates node with name nname
pnode create_node(char nname)
{
	pnode new_node = (pnode)calloc(1, sizeof(node));
	new_node->name = nname;
	new_node->d = INFINITY;
	new_node->pi = '-';
	new_node->next_node = NULL;
	new_node->edges = NULL;
	return new_node;
}
// function implementations
bool is_empty(pnode G)
{
	return !G;
}
char get_name(pnode G)
{
	return is_empty(G) ? '-' : G->name;
}
pnode set_name(pnode G, char name)
{
	if (!is_empty(G))
		G->name = name;
	return G;
}
pedge get_edges(pnode G)
{
	return is_empty(G) ? NULL : G->edges;
}
pnode set_edges(pnode G, pedge E)
{
	if (!is_empty(G))
		G->edges = E;
	return G;
}
pnode get_next(pnode G)
{
	return is_empty(G) ? NULL : G->next_node;
}
// see node_cons() for the corresponding "set-next" function
double get_d(pnode G)
{
	return is_empty(G) ? INFINITY : G->d;
}
pnode set_d(pnode G, double d)
{
	if (!is_empty(G))
		G->d = d;
	return G;
}
char get_pi(pnode G)
{
	return is_empty(G) ? '-' : G->pi;
}
pnode set_pi(pnode G, char pi)
{
	if (!is_empty(G))
		G->pi = pi;
	return G;
}
// node_cons: connects two nodes in adjacency list
pnode node_cons(pnode first, pnode second)
{
	if (is_empty(first))
		return NULL;
	first->next_node = second;
	return first;
}
// add_node: adds a new node with name nname to adjacency list G
//           in lexicographical order. If it already exists
//           in graph, nothing is done
pnode add_node(pnode G, char nname)
{
	// TODO
	return G;
}
// rem_node: removes node with name name from adjacency list G
//           if node does not exist, nothing happens
pnode rem_node(pnode G, char name)
{
	// TODO
	return G;
}
// get_node: returns pointer to node with name name from adjacency list G
pnode get_node(pnode G, char name)
{
	// TODO
	return G;
}
// get_node: returns true if node with name name exists in adjacency list G
//           false otherwise
bool find_node(pnode G, char name)
{
	return is_empty(G)	   ? false :
	       get_name(G) == name ? true :
				     find_node(G->next_node, name);
}
// create_edge: creates edge
pedge create_edge(char to, double weight)
{
	pedge new_edge = (pedge)calloc(1, sizeof(edge));
	new_edge->to = to;
	new_edge->weight = weight;
	return new_edge;
}
bool edge_empty(pedge E)
{
	return !E;
}
char get_to(pedge E)
{
	return edge_empty(E) ? '-' : E->to;
}
pedge set_to(pedge E, char to)
{
	if (!edge_empty(E))
		E->to = to;
	return E;
}
double get_weight(pedge E)
{
	return edge_empty(E) ? INFINITY : E->weight;
}
pedge set_weight(pedge E, double weight)
{
	if (!edge_empty(E))
		E->weight = weight;
	return E;
}
pedge get_next_edge(pedge E)
{
	return edge_empty(E) ? NULL : E->next_edge;
}
// edge_cons: connects two edges in edge list
pedge edge_cons(pedge first, pedge second)
{
	if (edge_empty(first))
		return NULL;
	first->next_edge = second;
	return first;
}
// upd_edge: updates edge E to new weight
pedge upd_edge(pedge E, double weight)
{
	// TODO
	return E;
}
// _add_edge: creates and connects new edge to edge-list
pedge _add_edge(pedge E, char to, double weight)
{
	// TODO
	return E;
}
// add_edge: adds an edge to G by finding correct start node
//           and then calling _add_edge to create new edge
void add_edge(pnode G, char from, char to, double weight)
{
	// TODO
}
// _find_edge: finds edge in edge-list
bool _find_edge(pedge E, char to)
{
	// TODO
	return false;
}
// find_edge: returns true if edge between from and to exists, false otherwise
bool find_edge(pnode G, char from, char to)
{
	// TODO
	return false;
}
// _edge_cardinality: returns the number of edges from one node
int _edge_cardinality(pedge E)
{
	// TODO
	return 0;
}
// edge_cardinality: returns the total number of edges in G
int edge_cardinality(pnode G)
{
	return 0;
}
// _self_loops: returns the number of edges going back to
//              source node
int _self_loops(pedge E, char src)
{
	// TODO
	return 0;
}
// self_loops: counts the number of self-loops, i.e. edges to and from
//             the same node
int self_loops(pnode G)
{
	// TODO
	return 0;
}
// _rem_edge: removes edge from edge-list
pedge _rem_edge(pedge E, char to)
{
	// TODO
	return E;
}
// rem_edge: removes edge from G
void rem_edge(pnode G, char from, char to)
{
	// TODO
}
// remove_all_edges_to: removes all edges going towards node with name name
void remove_all_edges_to(pnode G, char name)
{
	// TODO
}
// remove_all_edges_from: removes all edges from node with name name
void remove_all_edges_from(pnode G, char name)
{
	// TODO
}
// node_cardinality: returns the number of nodes in G
int node_cardinality(pnode G)
{
	// TODO
	return 0;
}
// name_to_pos: returns position of node with name c, -1 if not found
int name_to_pos(pnode G, char c)
{
	// TODO
	return -1;
}
// pos_to_name: returns name of node at position pos in G
char pos_to_name(pnode G, int pos)
{
	// TODO
	return '-';
}
// list_to_pos: creates adjacency matrix from adjacency list
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES])
{
	// TODO
}
