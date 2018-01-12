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

int main(int argc, char * argv[])
{
	WordHelper w;
	
	for (int i = 1; i < argc; i++) w.letters.push_back((char) *argv[i]); 

	w.powerSetEnum();//enumerate all of the possible sets of words
	w.permuteWords();//permute all of the possible sets
	w.checkDict();   //check all of the permutation of sets against a dictionary
	
	return 0; 
}

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

void WordHelper::checkDict()
{
	ifstream words; 
	string word; 
	set <string> dictionary; 
	
	words.open("words.txt"); 

	while(words >> word) dictionary.insert(word); 

	for(auto it = possibleWords.begin(); it != possibleWords.end(); it++)
		if(dictionary.find(*it) != dictionary.end()) cout << *it << endl;
}
