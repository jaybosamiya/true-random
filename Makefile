all: true_random.o tester

tester: tester.c true_random.o

true_random.o: true_random.c true_random.h

clean:
	rm -f tester true_random.o
