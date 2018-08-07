/* AUTHOR: Frankie Betancourt
 * DATE: 1/6/18
 * DESCRIPTION: This program takes in a list of letters and trys to find
 * what words you can spell with them. It gets pretty slow at around 9
 * letters.
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class WordHelper{
	public:
		vector <char> letters; 
		set <string> possibleWords; 
		set <string> letterSets; 
		void powerSetEnum(); 
		void permuteWords(); 
		void checkDict(); 
};

/* Sort completed strings by length */
struct stringLen {
  bool operator() (const string lhs_str, const string rhs_str) {
    const size_t lhs_len = lhs_str.length(); 
    const size_t rhs_len = rhs_str.length(); 
   
    /* If the length is the same, default to normal string sorting */
    if ( lhs_len == rhs_len ) { 
      return (rhs_str < lhs_str); 
    }

    return (rhs_len < lhs_len);
  }
};

int main(int argc, char * argv[])
{
	WordHelper w;
	
	for (int i = 1; i < argc; i++) w.letters.push_back((char) *argv[i]); 

  /* enumerate all of the possible sets of words */
	w.powerSetEnum();
  /* permute all of the possible sets */
	w.permuteWords();
  /* check all of the permutation of sets against a dictionary */
	w.checkDict();
	
	return 0; 
}

/* Do a power set enumeration of all of the input letters */
void WordHelper::powerSetEnum()
{
	string possibleWord; 

	for (int i = 0; i < (1 << letters.size()); i++) {
		for (int j = 0; j < letters.size(); j++) {
			if(i & (1 << j)) possibleWord += letters[j]; 
		}
		letterSets.insert(possibleWord); 
		possibleWord = ""; 
	}
}

/* Find all of the permutations for all the strings in the power set */
void WordHelper::permuteWords()
{
	string stringToPermute; 
	for(auto it = letterSets.begin(); it != letterSets.end(); it++)
	{
		stringToPermute = *it; 
		sort(stringToPermute.begin(), stringToPermute.end()); 
		do {
			possibleWords.insert(stringToPermute); 	
		} while (next_permutation(stringToPermute.begin(), stringToPermute.end()));
	}
}

/* Check all of the permutations against a dictionary */
void WordHelper::checkDict()
{
	ifstream words; 
	string word; 
	set <string> dictionary; 
  set <string, stringLen> valid_words;
	
	words.open("words.txt"); 

	while(words >> word) dictionary.insert(word); 

  /* Do comparison of all words and put in a set */
	for(auto it = possibleWords.begin(); it != possibleWords.end(); it++)
		if (dictionary.find(*it) != dictionary.end()) {
      valid_words.insert(*it);
    }

  /* Print out the list of valid words */
  for ( auto it = valid_words.begin(); it != valid_words.end(); it++ ) {
    cout << *it << endl;
  }
}
