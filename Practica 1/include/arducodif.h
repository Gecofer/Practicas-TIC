
#ifndef __ARDUCODIF__

#define __ARDUCODIF__


/*
 * Función que codificada un mensaje
 * 
 * Entradas: una cadena de caracteres 'orig' con longitud 'nOrig'
 * 
 * Salidas: devuelve en cada componente de 'codif' y 'util' cada símbolo 
            codificado y el número de bits útiles de cada símbolo.
*/
void codificador (const char *orig, const int nOrig, char * codif, unsigned char *util);


/*
 * Función que codificada un símbolo
 * 
 * Entradas: dado un símbolo como entrada en el parámetro 'corig'
 * 
 * Salidas: devuelva como salida un byte con el código Morse en binario, 
 *          asumiendo que los puntos se codificarán con 0 y las rayas con 1. 
 *          En el parámetro de salida nUtil, se devolverá cuántos bits ocupa 
 *          el símbolo codificado.
*/
void codificaSimbolo (const char corig, char &ccodif, unsigned char &nUtil);


/*
 * Función que decodificada un mensaje
 * 
 * Entradas: una cadena de caracteres 'orig' con longitud 'nOrig'
 * 
 * Salidas: devuelve en cada componente de 'codif' y 'util' cada 
 *          símbolo codificado y el número de bits útiles de cada símbolo.
*/
void decodificador (const char *codif, const unsigned char *utiles, const int nCodif, char *decodif);


/*
 * Función que decodificada un símbolo
 * 
 * Entradas: un byte como entrada en el parámetro 'ccodif', que codifica un 
 *           símbolo Morse como entrada, y otro parámetro de entrada 'nUtils' 
 *           con el número de bits útiles de 'ccodif'
 *
 * Salidas: devuelva como salida en 'decodif' el símbolo decodificado, asumiendo 
 *          que los puntos se codifican con 0 y las rayas con 1.
*/
void decodificaSimboloMorse(const char ccodif, const unsigned char nUtils, unsigned char & decodif);


#endif





