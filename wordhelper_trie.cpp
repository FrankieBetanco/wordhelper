#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std; 

/* Used to sort the set of completed words by length */
struct sortByLength {
  bool operator() (const string lhs_str, const string rhs_str) {
    size_t lhs_len = lhs_str.length();
    size_t rhs_len = rhs_str.length();

    if (lhs_len == rhs_len) {
      return (lhs_str < rhs_str);
    }
    return (lhs_len < rhs_len);
  }
};

/* nodes in trie */
typedef struct Node
{
  vector <Node *> children;
  int end_word; /* marks whether the node is at the end of a word */
  char letter; 
} Node;

static inline Node *
create_node() 
{
  int i; 
  Node * newNode;

  newNode = new Node; 
  newNode->end_word = 0;

  return newNode;
}

/* reads in words file and returns a vector contains an entry for each word */
static inline vector <string> 
read_dictionary() 
{
  string line;
  ifstream infile; 
  vector <string> words; 
  
  infile.open("words.txt"); 

  while (getline(infile, line)) {
    words.push_back(line);
  }

  return words;
}

/* returns the index of the child of *node being searched for */
static inline int 
child_index(Node *node, char letter) 
{
  int i; 

  for (i = 0; i < node->children.size(); i++) {
    if (letter == node->children[i]->letter) {
      return i;
    }
  }

  return -1;
}

/* inserts a string word into the trie whos root is Node* root */
static inline void 
trie_insert(Node *root, string word)
{
  int i, child; 
  Node *newNode; 

  if (word.size() == 0) {
    root->end_word = 1;
    return;
  }

  child = child_index(root, word[0]);
  if (child >= 0) {
    trie_insert(root->children[child], word.substr(1));
  } else {
    newNode = create_node();
    newNode->letter = word[0];
    root->children.push_back(newNode);
    trie_insert(newNode, word.substr(1)); 
  }
}

/* remove a letter from the set, and return a set without that letter */
static inline multiset <char> 
new_set_without(multiset <char> old_set, char letter) 
{
  old_set.erase(old_set.find(letter));
  return old_set;
}

/* search through the trie for words that can be created by the multiset
   letters */
static inline void
find_words(Node *root, multiset <char> letters, string current, 
    set <string, sortByLength> &valid_words)
{
  int child;

  if (root->end_word) {
    valid_words.insert(current);
  }

  if (root->children.size() == 0) {
    return;
  }

  for (auto it = letters.begin(); it != letters.end(); it++) {
    child = child_index(root, *it);
    if (child >= 0) {
      find_words(root->children[child], new_set_without(letters, *it), 
          current + *it, valid_words);
    }
  }
}

int 
main(int argc, char **argv) 
{
  int num_letters, i; 
  Node *root;
  multiset <char> letters;
  vector <string> words; 
  set <string, sortByLength> valid_words;
  string line; 

  words = read_dictionary();
  root = create_node();
  for (i = 0; i < words.size(); i++) {
    trie_insert(root, words[i]);
  }

  cout << "Enter set of letters: ";
  while (getline(cin, line)) {
    cout << "Searching for: " << line << endl;
    num_letters = line.length();
    for (i = 0; i < num_letters; i++) {
      letters.insert(line[i]);
    }
    find_words(root, letters, "", valid_words);
    cout << "found:" << endl;
    for (auto it = valid_words.begin(); it != valid_words.end(); it++) {
      cout << *it << endl;
    }
    cout << "found " <<  valid_words.size() << " words found for " << line 
      << endl;
    letters.clear();
    valid_words.clear();
    cout << "Enter a word: ";
  }

  return 0;
}
