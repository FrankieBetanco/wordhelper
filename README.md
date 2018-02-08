Wordhelper takes a list of letters on the command line and generates a
list of words you can spell. 

Basic Function
==============
It basically works by: 
1) inserting all of the letters into a vector of chars
2) generating a power set enumeration of that vector
3) generating all of the combinations of all the power sets, 
   and then putting all of those permutations into a new vector
   of strings
4) check all of the strings that were permuted against the dictionary

Run time
========
It's ludicrously slow. O((2^n)!) slow, in fact. This is due in large part
to the fact that there are n! combinations for each of the sets within 
the power set. Not only this, setting up the dictionary file takes O(log n)
and searching for each word takes O(log n). The run time in total ends up
being:

generating strings +setting up dictionary + searching dictionary for strings
     (2^n)!        +       log(k)         +          log( (2^n)! )

Ultimately, this program sucks. It does, however, help me cheat at board
games, which is what I designed it to do. I'll revisit this at some
point in the future to figure out a better way to do this.
