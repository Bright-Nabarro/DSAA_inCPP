app: s.o three_hash.o
	g++ -o app -g s.o three_hash.o

s.o: s.cpp three_hash.h
	g++ -std=c++20 -c -g s.cpp

three_hash.o: three_hash.cpp three_hash.h
	g++ -c -g three_hash.cpp

.PHONY: clean
clean:
	rm -f app s.o three_hash.o

