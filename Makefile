all: true_random.o tester generate_constant_stream

tester: tester.c true_random.o

generate_constant_stream: generate_constant_stream.c true_random.o

true_random.o: true_random.c true_random.h

clean:
	rm -f tester generate_constant_stream true_random.o
