all: wordhelper

wordhelper: wordhelper.cpp
	g++ -std=c++11 wordhelper.cpp -o wordhelper

clean: 
	rm wordhelper
