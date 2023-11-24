e.out: main.o caculate.o to_post.o
	g++ -g main.o caculate.o to_post.o -o e.out

main.o: main.cpp caculate.h
	g++ -g -c main.cpp

caculate.o: caculate.cpp caculate.h
	g++ -g -c caculate.cpp

to_post.o: ../23/to_post.cpp ../23/to_post.h
	g++ -g -c ../23/to_post.cpp

clean: 
	rm edit main.o caculate.o to_post.o
