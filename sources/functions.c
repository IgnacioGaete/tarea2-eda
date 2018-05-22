#include "../headers/functions.h"

// Add words contained in a line to the dictionary's data
/* READY */
void addWords(Dictionary *dictionary,char *line,int mode){
	if((mode!=0)&&(mode!=1)){
		printf("ERROR (addWords): Variable \'mode\' solo puede valer 0 ó 1.\n");
		return;
	}
	char *word=strtok(line,delimits);
	while(word!=NULL){
		if(!wordExist(dictionary->data,lowerCase(word))){
			insertWord(dictionary->data,lowerCase(word));
			dictionary->size++;
			if(mode==1)
				printf("%s: Agregada con éxito.\n",lowerCase(word));
		}
		else
			if(mode==1)
				printf("%s: Ya existe en el diccionario.\n",lowerCase(word));
		word=strtok(NULL,delimits);
	}
	return;
}

// Function that allows to delete a word from the "trie"
/* READY */
void deleteWord(TrieNode *tr, char *word){
	char c=(*word=='\0')?'*':*word;
	int i;
	for(i=0;i<ALPHABET_SIZE;i++){
		if(tr->child[i]!=NULL){
			if(tr->child[i]->letter==c){
				if(c!='*')
					deleteWord(tr->child[i],word+1);
				else{
					free(tr->child[i]);
					tr->child[i]=NULL;
				}
				return;
			}
		}
	}
	return;
}

// Destroys the Trie
/* READY */
void destroyTrie(TrieNode *tr){
	if(tr==NULL)
		return;
	int i;
	for(i=0;i<ALPHABET_SIZE;i++)
		destroyTrie(tr->child[i]);
	free(tr);
	return;
}

// Look for at least one TrieNode that contains a '*' as letter value
/* READY */
int emptyNode(TrieNode *tr){
	if(tr==NULL)
		return 1;
	if(tr->letter=='*')
		return 0;
	int i;
	for(i=0;i<ALPHABET_SIZE;i++)
		if(!emptyNode(tr->child[i]))
			return 0;
	return 1;
}

// Gets and validates the path given by the user
/* READY */
char *getPath(int argc,char **argv){
	if(argc==1){
		printf("ERROR: Debe ingresar ubicación del archivo de texto.\n");
		exit(1);
	}
	else if(argc>2){
		printf("ERROR: Demasiados argumentos ingresados.\n");
		exit(1);
	}
	return argv[1];
}

// Obtains a string of characters from stdin
/* READY */
char *getString(void){
	char *buffer=(char*)calloc((size_t)MAX_LINE_LENGHT,sizeof(char));
	int i=0;
	printf("> Ingrese su opción: ");
	do{
		buffer[i]=(char)getchar();
		i++;
	} while(buffer[i-1]!='\n');
	buffer[i-1]='\0';
	printf("\n");
	return buffer;
}

// Initializes the dictionary
/* READY */
void initDictionary(Dictionary *dict,char *path){
	dict->size=0;
	dict->path=path;
	dict->data=(TrieNode*)calloc((size_t)1,sizeof(TrieNode));
	return;
}

// Function that allows to put the character "c" in the node pointed by "tr"
/* READY */
TrieNode *insertNode(TrieNode *tr, char c){
	if(tr==NULL)
		tr=(TrieNode*)calloc((size_t)1,sizeof(TrieNode));
	tr->letter=c;
	return tr;
}

// Function that allows to insert a new word in the "trie"
/* READY */
void insertWord(TrieNode *tr, char *word){
	if(tr==NULL)
		return;
	int i;
	char c=(*word=='\0')?'*':*word;
	for(i=0;i<ALPHABET_SIZE;i++){
		if(tr->child[i]!=NULL){
			if(tr->child[i]->letter==c){
				if(c!='*')
					insertWord(tr->child[i],word+1);
				return;
			}
		}
	}
	for(i=0;i<ALPHABET_SIZE;i++){
		if(tr->child[i]==NULL){
			tr->child[i]=insertNode(tr->child[i],c);
			if(c!='*')
				insertWord(tr->child[i],word+1);
			return;
		}
	}
	return;
}

// Translate the option of the user into numbers that represent different options
/* READY */
int interpretOption(char *string){
	if(strlen(string)==0)
		return 6;//exit the program
	string=lowerCase(string);
	switch(*string){
		case '+':
			if(onlyWords(string+1)){
				return 2;
			}
			return -2;
		case '-':
			if(onlyWords(string+1))
				return 3;
			return -3;
		case '!':
			if(strlen(string)==1)
				return 4;
			return -4;
		case '?':
			if(strlen(string)==1)
				return 5;
			return -5;
		default:
			if(onlyLetters(string))
				return 1;
			if((*string>='a')&&(*string<='z'))
				return -1;
			return 0;
	}
}

// Change upper to lower case in a word
/* READY */
char *lowerCase(char *word){
	int i;
	for(i=0;i<strlen(word);i++)
		if((word[i]<='Z')&&(word[i]>='A'))
			word[i]=word[i]-'A'+'a';
	return word;
}

// Verifies if the string only have letters
/* READY */
int onlyLetters(char *string){
	string=lowerCase(string);
	int i;
	for(i=0;i<strlen(string);i++)
		if((string[i]<'a')||(string[i]>'z'))
			return 0;
	return 1;
}

// Verifies if the string only have words
/* READY */
int onlyWords(char *string){
	char temp[MAX_LINE_LENGHT]={[0 ... MAX_LINE_LENGHT-1]='\0'};
	strcpy(temp,string);
	char *word=strtok(temp," ");
	if(word==NULL)
		return 0;
	while(word!=NULL){
		if(!onlyLetters(word))
			return 0;
		word=strtok(NULL," ");
	}
	return 1;
}

// Prints all the words that starts with tr->letter
/* READY */
void printChildWords(TrieNode *tr,char *buffer,int pos){
	if(tr==NULL)
		return;
	*(buffer+pos)=(tr->letter=='*')?',':tr->letter;
	int i;
	for(i=0;i<ALPHABET_SIZE;i++)
		printChildWords(tr->child[i],buffer,pos+1);
	if(*(buffer+pos)==',')
		printf("%s ",buffer);
	*(buffer+pos)='\0';
	return;
}

// Prints all the words stored in *tr separated by tabs
/* READY */
void printDictionary(Dictionary dictionary){
	char *buffer=(char*)calloc((size_t)20,sizeof(char));
	int i;
	for(i=0;i<ALPHABET_SIZE;i++){
		printChildWords(dictionary.data->child[i],buffer,0);
		if(dictionary.data->child[i]!=NULL)
			printf("\b\b \n\n");
	}
	free(buffer);
	return;
}

// Prints the functionalities of the program
/* READY */
void printOptions(void){
	printf("\n");
	printf("******************************************************************************\n");
	printf("*                                                                            *\n");
	printf("*                        Funcionalidades implementadas:                      *\n");
	printf("*                                                                            *\n");
	printf("* 1) Sugerir palabras: Ingrese una cadena de caracteres y el programa        *\n");
	printf("*    mostrará sugerencias de completación de palabra.                        *\n");
	printf("*                                                                            *\n");
	printf("* 2) Agregar palabras: Anteponer un signo \"+\" a la cadena, permite agregar   *\n");
	printf("*    palabras nuevas al diccionario (deben ir separadas por espacios).       *\n");
	printf("*                                                                            *\n");
	printf("* 3) Eliminar palabras: Anteponer un signo \"-\" a la cadena, permite eliminar *\n");
	printf("*    palabras del diccionario (deben ir separadas por espacios).             *\n");
	printf("*                                                                            *\n");
	printf("* 4) Mostrar diccionario completo: Si solo se escribe \"!\" se mostrará por    *\n");
	printf("*    pantalla todas las palabras del diccionario (ADVERTENCIA: puede que no  *\n");
	printf("*    quepan todas adecuadamente).                                            *\n");
	printf("*                                                                            *\n");
	printf("* 5) Mostrar opciones: Si solo se escribe \"?\" se mostrarán por pantalla las  *\n");
	printf("*    opciones disponibles implementadas del programa.                        *\n");
	printf("*                                                                            *\n");
	printf("* 6) Salir del programa: Si solo se presiona ENTER el programa finalizará.   *\n");
	printf("*                                                                            *\n");
	printf("******************************************************************************\n");
	printf("\n");
	return;
}

// Prints a welcome message and the functionalities of the program
/* READY */
void printWelcome(void){
	printf("\n");
	printf("******************************************************************************\n");
	printf("*                                                                            *\n");
	printf("*                                ¡Bienvenid@!                                *\n");
	printf("*                              ELO320 - Tarea 2                              *\n");
	printf("*                                                                            *\n");
	printf("*                        Funcionalidades implementadas:                      *\n");
	printf("*                                                                            *\n");
	printf("* 1) Sugerir palabras: Ingrese una cadena de caracteres y el programa        *\n");
	printf("*    mostrará sugerencias de completación de palabra.                        *\n");
	printf("*                                                                            *\n");
	printf("* 2) Agregar palabras: Anteponer un signo \"+\" a la cadena, permite agregar   *\n");
	printf("*    palabras nuevas al diccionario (deben ir separadas por espacios).       *\n");
	printf("*                                                                            *\n");
	printf("* 3) Eliminar palabras: Anteponer un signo \"-\" a la cadena, permite eliminar *\n");
	printf("*    palabras del diccionario (deben ir separadas por espacios).             *\n");
	printf("*                                                                            *\n");
	printf("* 4) Mostrar diccionario completo: Si solo se escribe \"!\" se mostrará por    *\n");
	printf("*    pantalla todas las palabras del diccionario (ADVERTENCIA: puede que no  *\n");
	printf("*    quepan todas adecuadamente).                                            *\n");
	printf("*                                                                            *\n");
	printf("* 5) Mostrar opciones: Si solo se escribe \"?\" se mostrarán por pantalla las  *\n");
	printf("*    opciones disponibles implementadas del programa.                        *\n");
	printf("*                                                                            *\n");
	printf("* 6) Salir del programa: Si solo se presiona ENTER el programa finalizará.   *\n");
	printf("*                                                                            *\n");
	printf("******************************************************************************\n");
	printf("\n");
	return;
}

// Remove words contained in "string" from the dictionary "dict"
/* READY */
void removeWords(Dictionary *dictionary,char *line,int mode){
	if((mode!=0)&&(mode!=1)){
		printf("ERROR (removeWords): Variable \'mode\' solo puede valer 0 ó 1.\n");
		return;
	}
	char *word=strtok(line,delimits);
	while(word!=NULL){
		if(wordExist(dictionary->data,lowerCase(word))){
			deleteWord(dictionary->data,lowerCase(word));
			dictionary->size--;
			if(mode==1)
				printf("%s: Eliminada con éxito.\n",lowerCase(word));
		}
		else
			if(mode==1)
				printf("%s: No existe en el diccionario.\n",lowerCase(word));
		word=strtok(NULL,delimits);
	}
	return;
}

// Searches the string given and return the node that contains the last character
/* READY */
TrieNode *searchNode(TrieNode *tr,char *string){
	int i;
	if(*string=='\0'){
		for(i=0;i<ALPHABET_SIZE;i++)
			if(!emptyNode(tr->child[i]))
				return tr;
		return NULL;
	}
	for(i=0;i<ALPHABET_SIZE;i++)
		if(tr->child[i]!=NULL)
			if(tr->child[i]->letter==*string)
				return searchNode(tr->child[i],string+1);
	return NULL;
}

// Sugests words that start with "string", searching them in "dictionary"
/* READY */
void sugestWords(char *string,Dictionary dictionary){
	TrieNode *temp_node=NULL;
	if((temp_node=searchNode(dictionary.data,string))!=NULL){
		char temp_string[MAX_WORD_LENGHT]={[0 ... MAX_WORD_LENGHT-1]='\0'};
		strcpy(temp_string,string);
		printf("Palabras sugeridas: ");
		printChildWords(temp_node,temp_string,strlen(string)-1);
		printf("\b\b  \n\n");
	}
	else
		printf("¡No hay coincidencia!\n\n");
	return;
}

// Updates the dictionary, loading the words from the *.txt file to dictionary.data
/* READY */
void updateDictionary(Dictionary *dictionary){
	FILE *file=fopen(dictionary->path,"r");
	char line_buffer[MAX_LINE_LENGHT]={[0 ... MAX_LINE_LENGHT-1]='\0'};
	while(fscanf(file,"%s",line_buffer)!=EOF){
		addWords(dictionary,line_buffer,0);
	}
	printf("Total de palabras ingresadas al diccionario: %d\n\n",dictionary->size);
	return;
}

// Function that verifies whether the word exist in the "trie" or not
/* READY */
int wordExist(TrieNode *tr, char *word){
	if(tr==NULL)
		return 0;
	char c=(*word=='\0')?'*':*word;
	int i;
	for(i=0;i<ALPHABET_SIZE;i++){
		if(tr->child[i]!=NULL){
			if((tr->child[i]->letter=='*')&&(c=='*'))
				return 1;
			if((tr->child[i]->letter==c)&&(wordExist(tr->child[i],word+1)))
				return 1;
		}
	}
	return 0;
}
