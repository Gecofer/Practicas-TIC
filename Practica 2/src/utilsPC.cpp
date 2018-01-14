/*
AUTORES:
    - Gema Correa Fernandez
    - Samuel Cardenete Rodríguez
    - Pablo Parra Garófano
*/

/**
  * @file 
  * @brief Implementadas las funciones leerFichero y calcularProbabilidades
  *
  */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include "utilsPC.h"

using namespace std;


// Funcion que lee un fichero
void leerFichero(const char * filename, char *&contenido){
    
    ifstream entrada;
    entrada.open(filename, ios::in);
    
    // dirección desde donde buscar --> ir al final del fichero
    entrada.seekg(0, entrada.end);
    
    // para saber en qué posición estamos --> ver posicion para saber tamaño
    int length = entrada.tellg();
    
    contenido = new char[length];
    
    // entrada.beg: beginning of the stream
    entrada.seekg(0, entrada.beg);
    
    entrada.read(contenido, length);
    //cout << contenido << endl;
    entrada.close();
}

// -------------------------------------------------------------------------------- //

// Ordenación mediante Burbuja
void bubble_sort(float * probabilidades, char * codigos, int n) {

    float t_p;
    char t_c;

    for (int i=1; i<n; i++) {
        for (int j=0; j<n-1; j++) {
            if (probabilidades[j] < probabilidades[j+1]) {
                
                t_p = probabilidades[j];
                t_c = codigos[j];

                probabilidades[j] = probabilidades[j+1];
                codigos[j] = codigos[j+1];

                probabilidades[j+1] = t_p;
                codigos[j+1] = t_c;
            }
        }
    }
}

// -------------------------------------------------------------------------------- //

// Función que calcula las probabilidades de un caracter en un texto 
void calcularProbabilidades(const char *cadena, char *&codigos, float *&probabilidades, int &tamCodigos){

    // Obtenemos el tamaño del texto
    int tam_texto = strlen(cadena);

    // Estos son todos los posibles simbolos a aparecer
    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,; *" ;
    int simbolos[31] = {0};
    
    // Para obtener la posición 
    int p = 0;
    char c = cadena[0];

    while(c != '\0'){

        // Convertimos a mayuscula
        c = toupper(c);

        // Cogemos solo las letras del abecedario
        if (isalpha(c)) {
            simbolos[c - 'A']++;

        // Cogemos los símbolos de puntuación    
        } else {

            switch(c){
                case '.':
                    simbolos[26]++;
                break;
            }

            switch(c){
                case ',':
                    simbolos[27]++;
                break;
            }

            switch(c){
                case ';':
                    simbolos[28]++;
                break;
            }

            switch(c){
                case ' ':
                    simbolos[29]++;
                break;
            }

            switch(c){
                case '*':
                    simbolos[30]++;
                break;
            }
        }

        p++;
        c = cadena[p];
    }

    tamCodigos = 0;

    for (int i=0; i<31; i++) {
        if (simbolos[i] != 0) {
            codigos[tamCodigos] = alfabeto[i];
            //probabilidades[tamCodigos] = simbolos[i] / (double)tam_texto;
            probabilidades[tamCodigos] = simbolos[i];
            tamCodigos++;
        }
    }

    tamCodigos++;

    //cout << endl << "El tamaño del codigo es: " << tamCodigos++ << endl << endl;
    
    // Hacemos una copia de los dos vectores a modificar
    char * copia_codigos = codigos;
    float * copia_probabilidades = probabilidades;
   	
   	// Ordenamos por probabilidad
    bubble_sort(copia_probabilidades, copia_codigos, tamCodigos);
    
    /*
    for (int i=0; i<tamCodigos-1; i++){
        cout << "El caracter " << copia_codigos[i] << " tiene una probabilidad de " << copia_probabilidades[i] << endl;
    }
    */
    
}
