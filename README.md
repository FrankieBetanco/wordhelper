Wordhelper takes a list of letters on the command line and generates a
list of words you can spell. 

It basically works by: 
1) inserting all of the letters into a vector of chars
2) generating a power set enumeration of that vector
3) generating all of the combinations of all the power sets, 
   and then putting all of those permutations into a new vector
   of strings
4) check all of the strings that were permuted against the dictionary

It's ludicrously slow. O((2^n)!) slow, in fact. This is due in large part
to the fact that there are n! combinations for each of the sets within 
the power set. Not only this, setting up the dictionary file takes O(log n)
and searching for each word takes O(log n). The run time in total ends up
being:

generating strings
    |        setting up dictionary
	V        V
  (2^n)! + log(k) + log( (2^n)! )
                         ^
				         |
			            searching dictionary for strings

Ultimately, this program sucks. It does, however, help me cheat at board
games, which is what I designed it to do.
