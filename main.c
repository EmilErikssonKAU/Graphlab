#include <stdio.h>
#include <unistd.h>
#include "adjlist.h"
#include "ui.h"
void usage(char *name)
{
	printf("USAGE: %s [flags]\n\t-h\t-- help\n\t-u \t-- undirected mode\n\t-e\t-- echo input\n",
	       name);
}
int main(int argc, char *argv[])
{
	int opt;
	bool echo = false, dir = true;
	while ((opt = getopt(argc, argv, "heu")) != -1) {
		switch (opt) {
		case 'e':
			echo = true;
			break;
		case 'u':
			dir = false;
			break;
		default:
			usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	printf("INFO: Running in %sdirected mode\n", dir ? "" : "un");
	run(dir, echo);
	exit(EXIT_SUCCESS);
}
