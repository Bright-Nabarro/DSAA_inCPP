C_DEFAULT = g++ -std=c++20 -g
C_FLAGS = -I../testPrimer
VPATH = ../testPrimer
PRIMER = ../testPrimer
app: test.o next_prime.o 
	$(C_DEFAULT) test.o next_prime.o -o app

test.o: test.cpp probing.h
	$(C_DEFAULT) -c test.cpp $(C_FLAGS)

next_prime.o: next_prime.cpp next_prime.h
	$(C_DEFAULT) -c $(PRIMER)/next_prime.cpp $(C_FLAGS)

.PHONY: clean
clean:
	-rm app next_prime.o test.o