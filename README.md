Wordhelper takes a list of letters on the command line and generates a
list of words you can spell. I built it to help me cheat at board games. 

Revisiting
==========
I was intensely dissatisfied with how slow my original wordhelper was, so I 
decided to make a new version using a somewhat faster and prettier approach. 
What I did was to use a data structure called a 
[trie](https://en.wikipedia.org/wiki/Trie). It's pretty neat. 

Trie Solution
=============
This is implemented in wordhelper_trie.cpp

How it works is as follows: 
1) I insert all of the words found in 'words.txt' into the trie
2) Put the set of letters into a multiset
3) Do a depth first search of the tree, noting when a node that is the end of
the word is found. 
-At each recursive DFS call, remove the letter of the current node from the 
set, and call DFS on the set without the letter. 

Original Solution
=================
This is implemented in wordhelper.cpp

Disclaimer: This is terrible.
It basically worked by: 
1) inserting all of the letters into a vector of chars
2) generating a power set enumeration of that vector
3) generating all of the combinations of all the power sets, 
   and then putting all of those combinations into a new vector
   of strings
4) check all of the strings that were permuted against the dictionary

Feedback
========
As usual, please roast my code! I love feedback, and I don't care if you're nice about it or not. 
