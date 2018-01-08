

#ifndef __ARDUCODIF__

#define __ARDUCODIF__



void codificador (const char *orig, const int nOrig, char * codif, unsigned char *util);

void codificaSimbolo (const char corig, char &ccodif, unsigned char &nUtil);

void decodificador (const char *codif, const unsigned char *utiles, const int nCodif, char *decodif);

void decodificaSimboloMorse(const char ccodif, const unsigned char nUtils, unsigned char & decodif);


#endif





