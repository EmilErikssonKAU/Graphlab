// ui.h
#ifndef _UI_H
#define _UI_H
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "adjlist.h"
#define X -1
#define BUFSIZE 1024
pnode e_error(void);
void print_graph(pnode G);
void print_array(double *a, int size);
void print_menu(void);
char get_choice(char *prompt);
int get_int(char *prompt);
pnode ui_add_node(pnode G);
void ui_add_edge(bool directed, pnode G);
pnode ui_rem_node(pnode G);
void ui_rem_edge(bool directed, pnode G);
void ui_find_node(pnode G);
void ui_find_edge(pnode G);
void run(bool directed, bool echo);
#endif
