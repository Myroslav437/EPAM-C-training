all: build clean

build: Source.o 
	g++ Source.o -o vectorTest

Source.o:
	g++ -std=c++17 -c Source.cpp
	
clean:
	find . -name "*.o" -type f -delete