FLAGS= -Wall -pedantic -std=c++14 -iquote inc

___start__: program
	./program
program:Algorytmy_sortowania.o main.cpp
	g++ -o program Algorytmy_sortowania.o main.cpp

sort_algorithms.o:Algorytmy_sortowania.cpp
	g++ -c ${FLAGS}  Algorytmy_sortowania.cpp
	
clean:
	rm -f Algorytmy_sortowania.o program
