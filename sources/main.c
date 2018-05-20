#include "../headers/functions.h"

int main(int argc,char **argv){
	Dictionary dictionary;//defines a Dictionary structure
	initDictionary(&dictionary,getPath(argc,argv));//initializes the dictionary with default values
	printWelcome();//prints a welcome message and the functionalities of the program
	updateDictionary(&dictionary);//loads words from the *.txt file to the Dictionary structure
	char *option=NULL;//stores the option given by the user
	
	while(1){//main loop
		option=getString();//obtains the user's option
		switch(interpretOption(option)){
			case 1://sugests words from the dictionary
				sugestWords(option,dictionary);//prints sugestions based in word_attempt
				break;
			case 2://add words to the dictionary data
				addWords(&dictionary,option+1,1);
				printf("Tamaño actual del diccionario: %d\n\n",dictionary.size);
				break;
			case 3://delete words from the dictionary data
				removeWords(&dictionary,option+1,1);
				printf("Tamaño actual del diccionario: %d\n\n",dictionary.size);
				break;
			case 4://prints the entire dictionary data
				printDictionary(dictionary);
				break;
			case 5://prints the functionalities of the program
				printOptions();
				printf("Tamaño actual del diccionario: %d.\n\n",dictionary.size);
				break;
			case 6://End of the program
				destroyTrie(dictionary.data);//destroys the data of the dictionary
				return 0;
			case 0:
				printf("ERROR: Solo se permite uno de los siguientes símbolos al inicio: {+,-,!,?}\n\n");
				break;
			case -1:
				printf("ERROR: Palabra inválida (solo debe contener letras).\n\n");
				break;
			case -2:
				printf("ERROR: Debe ingresar palabras (solo letras) separadas por espacios.\n\n");
				break;
			case -3:
				printf("ERROR: Debe ingresar palabras (solo letras) separadas por espacios.\n\n");
				break;
			case -4:
				printf("ERROR: Mal uso de la opción \'!\'.\n\n");
				break;
			case -5:
				printf("ERROR: Mal uso de la opción \'?\'.\n\n");
				break;
		}
	}
}
