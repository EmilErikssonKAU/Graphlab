CFLAGS = -Wall
# Remove this -lm flag on Mac
LDLIBS = -lm

adjlist:		adjlist.o algorithm.o main.o ui.o
				gcc $(CLFAGS) -o adjlist adjlist.o algorithm.o ui.o main.o $(LDLIBS)

test:			adjlist_test algorithm_test
				@echo ----------------------------------------------------
				@echo Testing Adjacency List + Algorithms...
				@echo ----------------------------------------------------
				@./adjlist_test
				@./algorithm_test
				@echo ----------------------------------------------------

adjlist_test:	adjlist.o adjlist_test.o
				gcc $(CFLAGS) -o adjlist_test adjlist.o adjlist_test.o $(LDLIBS)

algorithm_test:	algorithm.h algorithm.c adjlist.h adjlist.c algorithm_test.c
				gcc $(CFLAGS) -o algorithm_test algorithm_test.c adjlist.c algorithm.c $(LDLIBS)

ui.o:			ui.c ui.h
				gcc $(CFLAGS) -c ui.c

adjlist.o:		adjlist.h adjlist.c algorithm.h algorithm.c ui.h ui.c main.c
				gcc $(CFLAGS) -c adjlist.c algorithm.c ui.c main.c
clean:
				rm -f *.o
				rm -f adjlist
				rm -f adjlist_test
				rm -f algorithm_test
