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
#include <Huffman.h>

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
    cout << endl << "TABLA DE PROBABILIDADES:" << endl;
    for (int i=0; i<tamCodigos-1; i++){
        cout << "El caracter " << codigos[i] << " tiene una probabilidad de " << probabilidades[i] << endl;
    }

    //Creamos la matriz que representa el arbol de Huffman
    int hf[64][4];

    //Definimos las variables para el tamaño del arbol y para el tamaño
    // del vector de orden:
    int tree_size = TAMALFABETO;

    construyeHuffman(codigos, probabilidades, hf, tree_size);
    cout << "MATRIZ ÁRBOL DE CODIFICACIÓN:" << endl;
    for (int i = 0; i < tree_size; i++){
       cout << i << " ";
        for (int j = 0; j < 4; j++){
            if (j==0){
                cout << (char)(hf[i][j]) << " ";
            } else {
                cout << (hf[i][j]) << " ";
            }
        }
        cout << endl;
    }
    
    char cadena[] = "ACE"; // prueba.txt
    // char cadena[] = "QUIJOTE"; // qujote.txt
    bool * codificado1;
    int tam_codificado;

    cout << endl << "El mensaje a codificar es: " << cadena << endl;
    cout << "La secuencia codificada es: ";
    codificarHuffman(cadena, hf, codificado1,  tree_size);
    
    /*for (int i = 0; i < 20; i++){
        cout << codificado[i];
    }
    cout << endl;*/

    char *codificado2 = "01100101"; // prueba.txt
    // char * codificado2 = "1000100100011101"; // quijote.txt
    cout << endl << endl << "La secuencia codificada es: " << codificado2 << endl;
    cout << "La secuencia decodificada es: ";
    decodificarHuffman(codificado2, hf, tree_size);
    cout << endl;

    return 0;
}



