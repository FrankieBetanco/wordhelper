default: wordhelper_trie

CFLAGS = -std=c++11 -O2

wordhelper: 
	$(CXX) $(FLAGS) -c wordhelper.cpp
	$(CXX) wordhelper.o wordhelper-garbage

wordhelper_trie: wordhelper_trie.cpp
	$(CXX) $(CFLAGS) -c wordhelper_trie.cpp
	$(CXX) wordhelper_trie.o -o wordhelper

clean: 
	rm -f *.o wordhelper wordhelper-garbage
