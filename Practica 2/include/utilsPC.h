#ifndef __UTILSPC__

#define __UTILSPC__


// Funcion que lee un fichero
void leerFichero(const char * filename, char *&contenido);

// Ordenación mediante Burbuja
void bubble_sort(float * probabilidades, char * codigos, int n);

// Función que calcula las probabilidades de un caracter en un texto 
void calcularProbabilidades(const char *cadena, char *&codigos, float *&probabilidades, int &tamCodigos);


#endif


