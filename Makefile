
#GNU Makefile

all:
	gcc -g3 usage.c logit.c -o logit.out

clean:
	rm -f *.o *.out

