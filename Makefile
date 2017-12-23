all: clean build run

clean:
	-rm -fR ./a.out

build:
	g++ main.cpp -std=c++17 -Wall -lncursesw -I. -g

run:
	./a.out
