
// Data Structures and Algorithms (DSA) UI for Graph (MBl 2024)
#include "ui.h"
#include "algorithm.h"
bool echo = false;
pnode e_error(void)
{
	printf("Graph is empty\n");
	return NULL;
}
void print_node_header(pnode G, int n)
{
	printf("%4c|", ' ');
	for (int i = 0; i < n; i++)
		printf("%3c  ", pos_to_name(G, i));
	printf("\n----+");
	for (int i = 0; i < n; i++)
		printf("-----");
	printf("\n");
}
void print_matrix(pnode G, double M[MAXNODES][MAXNODES], int n)
{
	print_node_header(G, n);
	for (int i = 0; i < n; i++) {
		printf("%4c|", pos_to_name(G, i));
		for (int k = 0; k < n; k++)
			if (M[i][k] == INFINITY)
				printf("%3c  ", '*');
			else
				printf("%3.0lf  ", M[i][k]);
		printf("\n");
	}
	printf("\n");
}
void print_graph(pnode G)
{
	int n = node_cardinality(G);
	if (is_empty(G))
		e_error();
	else {
		double M[MAXNODES][MAXNODES];
		for (int i = 0; i < n; i++)
			for (int k = 0; k < n; k++)
				M[i][k] = INFINITY;
		list_to_matrix(G, M);
		print_matrix(G, M, n);
	}
	printf("node cardinality: %d\n", node_cardinality(G));
	printf("edge cardinality: %d\n", edge_cardinality(G));
}
// prints the contents of integer array a from 0 up to size
void print_array(double *a, int size)
{
	printf("[");
	if (size == 0) {
		printf("]\n");
		return;
	}
	for (int i = 0; i < size; i++)
		if (a[i] != X)
			printf("%3.0lf%s", a[i], i < size - 1 ? ", " : "]");
		else
			printf("%3c%s", '*', i < size - 1 ? ", " : "]");
	printf("\n");
}
void print_char_array(char *a, int size)
{
	printf("[");
	if (size == 0) {
		printf("]\n");
		return;
	}
	for (int i = 0; i < size; i++)
		if (a[i] != X)
			printf("%3c%s", a[i], i < size - 1 ? ", " : "]");
		else
			printf("%3c%s", '*', i < size - 1 ? ", " : "]");
	printf("\n");
}
// prints the menu
void print_menu(void)
{
	printf("********************************\n");
	printf("m: menu\n");
	printf("v: view\n");
	printf("q: quit\n");
	printf("\n");
	printf("a: add node\n");
	printf("b: add edge\n");
	printf("\n");
	printf("d: delete node\n");
	printf("r: delete edge\n");
	printf("\n");
	printf("f: find node\n");
	printf("g: find edge\n");
	printf("\n");
	printf("W: Warshall\n");
	printf("F: Floyd\n");
	printf("D: Dijkstra\n");
	printf("P: Prim\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
// gets an input character
char get_choice(char *prompt)
{
	printf("%s", prompt);
	char buf[BUFSIZE];
	fgets(buf, BUFSIZE - 1, stdin);
	if (echo)
		printf("%c\n", buf[0]);
	return buf[0];
}
// gets an input integer
int get_int(char *prompt)
{
	printf("%s", prompt);
	char buf[BUFSIZE];
	fgets(buf, BUFSIZE - 1, stdin);
	if (!isdigit(buf[0])) {
		if (echo)
			printf("-1\n");
		return X;
	}
	if (echo)
		printf("%d\n", atoi(buf));
	return atoi(buf);
}

// gets input and adds an element to G
pnode ui_add_node(pnode G)
{
	char val;
	val = get_choice("Enter value to be added> ");
	if (echo)
		printf("%d\n", val);
	return isalpha(val) ? add_node(G, val) : G;
}
void ui_add_edge(bool directed, pnode G)
{
	if (is_empty(G))
		e_error();
	else {
		char from = get_choice("Enter from> "),
		     to = get_choice("Enter to> ");
		double weight = get_int("Enter weight> ");
		add_edge(G, from, to, weight);
		if (!directed)
			add_edge(G, to, from, weight);
	}
}
// gets input and adds an element to G
pnode ui_rem_node(pnode G)
{
	if (is_empty(G))
		return e_error();
	char val = get_choice("Enter value to be removed> ");
	if (echo)
		printf("%d\n", val);
	return rem_node(G, val);
}
void ui_rem_edge(bool directed, pnode G)
{
	if (is_empty(G))
		e_error();
	else {
		char from = get_choice("Enter from> "),
		     to = get_choice("Enter to> ");
		rem_edge(G, from, to);
		if (!directed)
			rem_edge(G, to, from);
	}
}
// gets input and searches for element in T
void ui_find_node(pnode G)
{
	if (is_empty(G))
		e_error();
	else {
		char val = get_choice("Enter value to search for> ");
		if (echo)
			printf("%d\n", val);
		printf("%c is a%smember\n", val,
		       find_node(G, val) ? " " : " non-");
	}
}
void ui_find_edge(pnode G)
{
	if (is_empty(G))
		e_error();
	else {
		char first = get_choice("Enter start node> ");
		char second = get_choice("Enter end node> ");
		printf("Edge between %c and %c %sfound\n", first, second,
		       find_edge(G, first, second) ? "" : "not ");
	}
}
void ui_dijkstra(pnode G)
{
	printf("Dijkstra\n");
	if (is_empty(G))
		e_error();
	else {
		int N = node_cardinality(G);
		double d[MAXNODES];
		char e[MAXNODES];
		char start = get_choice("Enter start node> ");
		if (!find_node(G, start))
			printf("Start node does not exist in graph\n");
		else {
			dijkstra(G, start, d, e);
			printf("d: ");
			print_array(d, N);
			printf("e: ");
			print_char_array(e, N);
		}
	}
}
void ui_prim(pnode G)
{
	printf("Prim\n");
	if (is_empty(G))
		e_error();
	else {
		int N = node_cardinality(G);
		double d[MAXNODES];
		char e[MAXNODES];
		char start = get_choice("Enter start node> ");
		if (!find_node(G, start))
			printf("Start node does not exist in graph\n");
		else {
			prim(G, start, d, e);
			printf("d: ");
			print_array(d, N);
			printf("e: ");
			print_char_array(e, N);
		}
	}
}
void ui_floyd(pnode G)
{
	printf("Floyd\n");
	if (is_empty(G))
		e_error();
	else {
		int N = node_cardinality(G);
		double W[MAXNODES][MAXNODES];
		floyd(G, W);
		print_matrix(G, W, N);
	}
}
void ui_warshall(pnode G)
{
	printf("Warshall\n");
	if (is_empty(G))
		e_error();
	else {
		int N = node_cardinality(G);
		double W[MAXNODES][MAXNODES];
		warshall(G, W);
		print_matrix(G, W, N);
	}
}
void run(bool directed, bool e)
{
	char val;
	pnode G = NULL;
	if (e)
		echo = true;
	print_menu();
	do {
		val = get_choice("menu> ");
		switch (val) {
		case 'm':
			print_menu();
			break;
		case 'v':
			print_graph(G);
			break;
		case 'q':
			printf("Quitting...\n");
			break;
		case 'a':
			G = ui_add_node(G);
			break;
		case 'b':
			ui_add_edge(directed, G);
			break;
		case 'd':
			G = ui_rem_node(G);
			break;
		case 'r':
			ui_rem_edge(directed, G);
			break;
		case 'f':
			ui_find_node(G);
			break;
		case 'g':
			ui_find_edge(G);
			break;
		case 'W':
			ui_warshall(G);
			break;
		case 'F':
			ui_floyd(G);
			break;
		case 'D':
			ui_dijkstra(G);
			break;
		case 'P':
			ui_prim(G);
			break;
		default:
			printf("Unknown command (%c)\n", val);
			break;
		}
	} while (val != 'q');
}
