all: wordhelper wordhelper_trie


wordhelper: wordhelper.cpp
	g++ -std=c++11 wordhelper.cpp -o wordhelper

wordhelper_trie: wordhelper_trie.cpp
	g++ -std=c++11 -c wordhelper_trie.cpp
	g++ -std=c++11 wordhelper_trie.o -o wordhelper_trie

clean: 
	rm wordhelper
	rm wordhelper_trie
