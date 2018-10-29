CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: testme


testme: testme.c 
	gcc -o testme testme.c $(CFLAGS)
	./testme


clean:
	rm -f *.o testme testme.exe *.gcov *.gcda *.gcno *.so *.out
