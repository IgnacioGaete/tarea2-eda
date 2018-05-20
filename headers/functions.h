#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global definitions
#define ALPHABET_SIZE   29
#define MAX_LINE_LENGHT 100
#define MAX_WORD_LENGHT 20

// Global variables
static char delimits[]="\t\v\r\f\n °|¬!1\"2#3$4%5&6/7(8)9=0?'\\¡¿@¨´*+~[{^]}`<>;,:._-─©";

// Structures:
typedef struct mtrie{
	char letter;
	struct mtrie *child[ALPHABET_SIZE];
} TrieNode;

typedef struct mdict{
	int size;
	char *path;
	TrieNode *data;
} Dictionary;

// Function declarations:

// Function that allows to insert a new word in the "trie"
void insertWord(TrieNode*,char*);

// Function that allows to delete a word from the "trie"
void deleteWord(TrieNode*,char*);

// Function that verifies whether the word is in the "trie" or not
int wordExist(TrieNode*,char*);

// Function that allows to put the character "c" in the node pointed by "tr"
TrieNode *insertNode(TrieNode*,char);

// Prints all the words stored in *tr
void printDictionary(Dictionary);

// Prints all the words that starts with tr->letter
void printChildWords(TrieNode*,char*,int);

// Destroys the Trie
void destroyTrie(TrieNode*);

// Obtains a string of characters from stdin
char *getString(void);

// Change upper to lower case in a word
char *lowerCase(char*);

// Gets and validates the path given by the user
char *getPath(int,char**);

// Initializes the dictionary
void initDictionary(Dictionary*,char*);

// Add words contained in a line to the dictionary's data
void addWords(Dictionary*,char*,int);

void removeWords(Dictionary*,char*,int);

// Updates the dictionary, loading the words from the *.txt file to dictionary.data
void updateDictionary(Dictionary*);

// Sugests words that start with "string", searching them in "dictionary"
void sugestWords(char*,Dictionary);

// Searches the string given and return the node that contains the last character
TrieNode *searchNode(TrieNode*,char*);

// Look for at least one TrieNode that contains a '*' as letter value
int emptyNode(TrieNode*);

int interpretOption(char*);

int onlyWords(char*);

int onlyLetters(char*);

// Prints a welcome message and the functionalities of the program
void printWelcome(void);

// Prints the functionalities of the program
void printOptions(void);

#endif
