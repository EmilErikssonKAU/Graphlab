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

	if(is_empty(G)){
		G = create_node(nname);
		return G;
	}

	if (find_node(G, nname)) {
		printf("node alredy exists \n");
		return G;
	}

	pnode current = G;
	pnode newnode = create_node(nname);

	if(nname < get_name(G)){
		node_cons(newnode, G);
		return newnode;
	}
	while (get_next(current) != NULL &&  get_name(get_next(current))  < get_name(newnode)){
		current = get_next(current);
	}
	node_cons(newnode, get_next(current));
	node_cons(current, newnode);

	return G;
	
}


// rem_node: removes node with name name from adjacency list G
//           if node does not exist, nothing happens
pnode rem_node(pnode G, char name)
{	

	if (find_node(G, name) == false) {
		printf("node does not exist \n");
		return G;
	}

	if (get_name(G) == name){
		G = get_next(G);
		return G;
	}

	pnode current = G; 

	while(get_next(current)!= NULL){
	
			if(get_name((get_next(current))) == name){
			node_cons(current, get_next((get_next(current))));
			break;
		}
		current = get_next(current);
	}
	 
	return G; 
}


// get_node: returns pointer to node with name name from adjacency list G
pnode get_node(pnode G, char name)
{

	while(get_next(G) != NULL){

		if(get_name(G) == name){
			break; 
		}
		G = get_next(G);
	}
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
	set_weight(E, weight);
	return E;
}


// _add_edge: creates and connects new edge to edge-list
pedge _add_edge(pedge E, char to, double weight)
{
	if(edge_empty(E)){
		E = create_edge(to, weight);
	}

	pedge newedge = create_edge(to, weight);
	pedge current_edge = E;
	
	if(to < get_to(E)){
		edge_cons(newedge, E);
		return newedge;
	}

	while ( get_next_edge(current_edge) != NULL &&  get_to(get_next_edge(current_edge)) < get_to(newedge)){
		current_edge =   get_next_edge(current_edge);
	}
	edge_cons(newedge		, 	get_next_edge(current_edge));
	edge_cons(current_edge	,	newedge);


	return E;

}


// add_edge: adds an edge to G by finding correct start node
//           and then calling _add_edge to create new edge
void add_edge(pnode G, char from, char to, double weight)
{

	pnode current = get_node(G, from);

	set_edges(G, _add_edge(get_edges(current), to, weight));

}


// _find_edge: finds edge in edge-list
bool _find_edge(pedge E, char to)
{
	if(edge_empty(E)){
		return false; 
	}

	else{
		if(get_to(E) == to){
			return true;
		}
		else{
			_find_edge(get_next_edge(E), to);
		}
	}

	return true;

}


// find_edge: returns true if edge between from and to exists, false otherwise
bool find_edge(pnode G, char from, char to)
{
	
	pnode current = get_node(G, from);

	if(_find_edge(get_edges(current), to)){
		return true; 
		}
	else{
		return false;
	}
	
	
	

	
}


// _edge_cardinality: returns the number of edges from one node
int _edge_cardinality(pedge E)
{

	if (E == NULL){
		return 0;
	}
	int count  = 0; 
	while(get_next_edge(E) != NULL){
		E = get_next_edge(E);
		count++;
	}
	return count;

	return 0;
}


// edge_cardinality: returns the total number of edges in G
int edge_cardinality(pnode G)
{
	if(is_empty(G)){
		return 0; 
	}
	int count = 0;

	while(G->next_node != NULL){
		count = count + _edge_cardinality(get_edges(G));
		G = get_next(G);
		}

	return count; 
}


// _self_loops: returns the number of edges going back to
//              source node
int _self_loops(pedge E, char src)
{
	if(edge_empty(E)){
		return 0;
	}


	
	int count = 0;

	pedge current_edge = E;  
	
	while (current_edge != NULL ){
		

		if(current_edge->to == src){
			count++;
		}
		current_edge = current_edge->next_edge;
	}

	return count; 
	

}


// self_loops: counts the number of self-loops, i.e. edges to and from
//             the same node
int self_loops(pnode G)
{

	if(is_empty(G)){
		return 0;
	}



	pnode current_node = G;

	int count = 0;





	while(!is_empty(current_node)){
		
		count = count + _self_loops(get_edges(current_node), get_name(current_node));


		current_node = get_next(current_node);

	}


	return count;


	
	

	//todo

	return 0;
}


// _rem_edge: removes edge from edge-list
pedge _rem_edge(pedge E, char to)
{
	
if (_find_edge(E, to) == false) {
		printf("node does not exist \n");
		return E;
	}

	if (get_to(E) == to){
		E = get_next_edge(E);
		return E;
	}

	pedge current = E; 

	while(get_next_edge(current) != NULL){
	

		if(get_to(current) == to){
			edge_cons(current, get_next_edge(get_next_edge(current)));
			break;
		}
		current = get_next_edge(current);
	}
	 
	return E; 


}


// rem_edge: removes edge from G
void rem_edge(pnode G, char from, char to)
{

	pnode curent = get_node(G, from);

	_rem_edge(get_edges(curent), to);
}


// remove_all_edges_to: removes all edges going towards node with name name
void remove_all_edges_to(pnode G, char name)
{
	if(is_empty(G)){
		return;
	}

	pnode current_node = G;


	while(current_node != NULL){
		
		//pedge temp = get_edges(current_node); 
		current_node = get_next(current_node); 
		_rem_edge(get_edges(current_node), name);


		


	
	}

	

}


// remove_all_edges_from: removes all edges from node with name name
void remove_all_edges_from(pnode G, char name)
{
	
	
	pnode current_node = get_node(G, name);


	pedge current_edge = get_edges(current_node);

	while(current_edge != NULL){
		pedge temp = current_edge; 
        current_edge = get_next_edge(current_edge);  
        free(temp); 
	}  

	set_edges(current_node, NULL);
	

	


}


// node_cardinality: returns the number of nodes in G
int node_cardinality(pnode G)
{

	if(is_empty(G)){
		return 0; 
	}


	int count  = 0; 
	while(get_next(G) != NULL){
		G = get_next(G);
		count++;
	}



	return count+1;
}


// name_to_pos: returns position of node with name c, -1 if not found
int name_to_pos(pnode G, char c)
{
	int count = 0; 

	while(G != NULL){

		if(get_name(G) == c){
			return count; 
		}
		G = get_next(G);
		count++;
	}
	
	return -1;
}


// pos_to_name: returns name of node at position pos in G
char pos_to_name(pnode G, int pos)
{
	if(is_empty(G)){
		return '-';
	} 
	for(int i = 0; i < pos; i++){
		G = get_next(G);
	}
	return G->name;	
}


// list_to_pos: creates adjacency matrix from adjacency list
void list_to_matrix(pnode G, double matrix[MAXNODES][MAXNODES]) {
    if (is_empty(G)) {
        return;
    }

    for (int i = 0; i < MAXNODES; i++) {
        for (int j = 0; j < MAXNODES; j++) {
            matrix[i][j] = 0;
        }
    }
    
    for (int i = 0; i < node_cardinality(G); i++) {
        pnode current = get_node(G, pos_to_name(G, i));

        pedge currentedge = get_edges(current);
        while (currentedge != NULL) {
            int pos = name_to_pos(G, get_to(currentedge));
                matrix[i][pos] = 1;
            currentedge =  get_next_edge(currentedge);
        }
    }
}

