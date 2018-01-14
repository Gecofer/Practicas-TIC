/*
AUTORES:
	- Gema Correa Fernandez
	- Samuel Cardenete Rodríguez
	- Pablo Parra Garófano
*/


#include "ticcommardu.h"
#include "arducodif.h"
#include <ctype.h>


// Función que codifica una cadena
void codificador (const char *orig, const int nOrig, char * codif, unsigned char *util){

    for (int i = 0; i < nOrig; i++){

    	char byte_salida;
    	unsigned char util_salida;

    	// Codificamos uno a uno los símbolos de la cadena:
        codificaSimbolo(toupper(orig[i]), byte_salida, util_salida);

        // Guardamos los símbolos codificados y su tamanio util:
        codif[i] = byte_salida;
        util[i] = util_salida;
    }
}


// Función que decodifica una cadena
void decodificador (const char *codif, const unsigned char *utiles, const int nCodif, char *decodif){

    for (int i = 0; i < nCodif; i++){

    	unsigned char letra_decodificada;

    	// Codificamos uno a uno los símbolos de la cadena:
    	decodificaSimboloMorse(codif[i], utiles[i], letra_decodificada);

    	decodif[i] = letra_decodificada;
    	
    }
}


// Función que codifica un símbolo Morse
void codificaSimbolo(const char corig, char & ccodif, unsigned char & nUtil){
	
	switch(corig){
		case 'A':
			ccodif = 0b00000001;
			nUtil = 2;
		break;
		case 'B':
			ccodif = 0b00001000;
			nUtil = 4;
		break;
		case 'C':
			ccodif = 0b00001010;
			nUtil = 4;
		break;
		case 'D':
			ccodif = 0b00000100;
			nUtil = 3;
		break;
		case 'E':
			ccodif = 0b00000000;
			nUtil = 1;
		break;
		case 'F':
			ccodif = 0b00000010;
			nUtil = 4;
		break;
		case 'G':
			ccodif = 0b00000110;
			nUtil = 3;
		break;
		case 'H':
			ccodif = 0b00000000;
			nUtil = 4;
		break;
		case 'I':
			ccodif = 0b00000000;
			nUtil = 2;
		break;
		case 'J':
			ccodif = 0b00000111;
			nUtil = 4;
		break;
		case 'K':
			ccodif = 0b00000101;
			nUtil = 3;
		break;
		case 'L':
			ccodif = 0b00000100;
			nUtil = 4;
		break;
		case 'M':
			ccodif = 0b00000011;
			nUtil = 2;
		break;
		case 'N':
			ccodif = 0b00000010;
			nUtil = 2;
		break;
		case 'O':
			ccodif = 0b00000111;
			nUtil = 3;
		break;
		case 'P':
			ccodif = 0b00000110;
			nUtil = 4;
		break;
		case 'Q':
			ccodif = 0b00001101;
			nUtil = 4;
		break;
		case 'R':
			ccodif = 0b00000010;
			nUtil = 3;
		break;
		case 'S':
			ccodif = 0b00000000;
			nUtil = 3;
		break;
		case 'T':
			ccodif = 0b00000001;
			nUtil = 1;
		break;
		case 'U':
			ccodif = 0b00000001;
			nUtil = 3;
		break;
		case 'V':
			ccodif = 0b00000001;
			nUtil = 4;
		break;
		case 'W':
			ccodif = 0b00000011;
			nUtil = 3;
		break;
		case 'X':
			ccodif = 0b00001001;
			nUtil = 4;
		break;
		case 'Y':
			ccodif = 0b00001011;
			nUtil = 4;
		break;
		case 'Z':
			ccodif = 0b00001100;
			nUtil = 4;
		break;
		case ' ':
			ccodif = 0b00000000;
			nUtil = 5;
		break;
		case '.':
			ccodif = 0b00000001;
			nUtil = 5;
		break;
		case ';':
			ccodif = 0b00000010;
			nUtil = 5;
		break;
		case ',':
			ccodif = 0b00000011;
			nUtil = 5;
		break;
	}
}


// Función que decodifica un símbolo Morse
void decodificaSimboloMorse(const char ccodif, const unsigned char nUtils, unsigned char & decodif){

	switch(nUtils){
		case 1:
			switch(ccodif){
				case 0b00000001:
					decodif = 'T';
				break;	
				case 0b00000000:
					decodif = 'E';
				break;	
			}
		break;
			
		case 2:
			switch(ccodif){
				case 0b00000011:
					decodif = 'M';
				break;	
				case 0b00000010:
					decodif = 'N';
				break;	
				case 0b00000000:
					decodif = 'I';
				break;	
				case 0b00000001:
					decodif = 'A';
				break;	
			}
		break;

		case 3:
			switch(ccodif){
				case 0b00000011:
					decodif = 'W';
				break;	
				case 0b00000001:
					decodif = 'U';
				break;	
				case 0b00000000:
					decodif = 'S';
				break;	
				case 0b00000010:
					decodif = 'R';
				break;	
				case 0b00000111:
					decodif = 'O';
				break;	
				case 0b00000101:
					decodif = 'K';
				break;	
				case 0b00000110:
					decodif = 'G';
				break;
				case 0b00000100:
					decodif = 'D';
				break;
			}
		break;

		case 4:
			switch(ccodif){
				case 0b00001100:
					decodif = 'Z';
				break;	
				case 0b00001011:
					decodif = 'Y';
				break;	
				case 0b00001001:
					decodif = 'X';
				break;	
				case 0b00000001:
					decodif = 'V';
				break;
				case 0b00001101:
					decodif = 'Q';
				break;
				case 0b00000110:
					decodif = 'P';
				break;
				case 0b00000100:
					decodif = 'L';
				break;
				case 0b00000111:
					decodif = 'J';
				break;
				case 0b00000000:
					decodif = 'H';
				break;
				case 0b00000010:
					decodif = 'F';
				break;
				case 0b00001010:
					decodif = 'C';
				break;

				case 0b00001000:
					decodif = 'B';
				break;
			}
		break;

		case 5:
			switch(ccodif){
				case 0b00000011:
					decodif = ',';
				break;	
				case 0b00000010:
					decodif = ';';
				break;	
				case 0b00000001:
					decodif = '.';
				break;	
				case 0b00000000:
					decodif = ' ';
				break;

			}
		break;
	}
}
