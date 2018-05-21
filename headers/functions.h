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

// Add words contained in "string" to the dictionary "dict"
void addWords(Dictionary*,char*,int);

// Deletes a word from the "Trie"
void deleteWord(TrieNode*,char*);

// Destroys the given "Trie"
void destroyTrie(TrieNode*);

// Looks for at least one "TrieNode" that contains a '*' as letter value
int emptyNode(TrieNode*);

// Gets and validates the path given by the user
char *getPath(int,char**);

// Obtains a string of characters from stdin
char *getString(void);

// Initializes the dictionary
void initDictionary(Dictionary*,char*);

// Function that allows to put the character "c" in the node pointed by "tr"
TrieNode *insertNode(TrieNode*,char);

// Function that allows to insert a new word in the "trie"
void insertWord(TrieNode*,char*);

// Translate the option of the user into numbers that represent different options
int interpretOption(char*);

// Change upper to lower case in a word
char *lowerCase(char*);

// Verifies if the string only have letters
int onlyLetters(char*);

// Verifies if the string only have words
int onlyWords(char*);

// Prints all the words that starts with tr->letter
void printChildWords(TrieNode*,char*,int);

// Prints all the words stored in *tr
void printDictionary(Dictionary);

// Prints the functionalities of the program
void printOptions(void);

// Prints a welcome message and the functionalities of the program
void printWelcome(void);

// Remove words contained in "string" from the dictionary "dict"
void removeWords(Dictionary*,char*,int);

// Searches the string given and return the node that contains the last character
TrieNode *searchNode(TrieNode*,char*);

// Sugests words that start with "string", searching them in "dictionary"
void sugestWords(char*,Dictionary);

// Updates the dictionary, loading the words from the *.txt file to dictionary.data
void updateDictionary(Dictionary*);

// Function that verifies whether the word is in the "trie" or not
int wordExist(TrieNode*,char*);

#endif
