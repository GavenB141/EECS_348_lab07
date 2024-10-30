main: main.cpp
	g++ -std=c++11 main.cpp -o main -Wall
clean:
	rm -f *.o main
