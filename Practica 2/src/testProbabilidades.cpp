/*
AUTORES:
    - Gema Correa Fernandez
    - Samuel Cardenete Rodríguez
    - Pablo Parra Garófano
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <utilsPC.h>

using namespace std;


int main(int argc, char** argv) {

    const char * filename = "data/prueba.txt";
    const int TAMALFABETO = 9;
    //const char * filename = "data/quijote.txt";
    //const int TAMALFABETO = 31;
    
    char * salida;
    char *codigos = new char[100];
    float *probabilidades = new float[100]; 
    int tamCodigos = 100;
    
    leerFichero(filename, salida);
    calcularProbabilidades(salida, codigos, probabilidades, tamCodigos);

    // Mostrar ordenadas las probabilidades
    for (int i=0; i<tamCodigos-1; i++){
    	cout << "El caracter " << codigos[i] << " tiene una probabilidad de " << probabilidades[i] << endl;
    }

    cout << endl;
}



