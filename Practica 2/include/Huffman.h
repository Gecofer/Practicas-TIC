#ifndef __HUFFMAN__

#define __HUFFMAN__


// Ordenación mediante Burbuja
void bubble_sort1(float * probabilidades, int * codigos, int n);

// Generar un árbol de codificación Huffman
void construyeHuffman(char *codigos, float * probabilidades, int hf[64][4], int & tree_size);

// Codificar un mensaje con el árbol de Huffman
void codificarHuffman(char * cadena, int hf[64][4], bool * &codificado, int tree_size);

// Decodificar una secuencia de bits con el ábrol de Huffman
void decodificarHuffman(char * codificado, int hf[64][4], int tree_size);


#endif