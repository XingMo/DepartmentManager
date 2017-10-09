all: main.o
	g++ main.o -o main
main.o: ./main.cpp
	g++ -std=c++11 -I./include -c ./main.cpp -o main.o
clean:
	rm *.o
