#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <Huffman.h>

using namespace std;

/* 
Creación de código Huffman
 - Ordenar los símbolos por probabilidad decreciente
 - Mientras quede más de un elemento en el vector, agrupar los dos símbolos de 
   menor probabilidad en un nuevo árbol, asignando “0” al hijo izquierda y “1” 
   al hijo derecha.
 - Asignar a la raíz su probabilidad: La suma de las probabilidades de los 
   elementos seleccionados en el vector.
 - Asignar el contenido (código) del primer elemento seleccionado como hijo izquierda,
   y el contenido del segundo como hijo derecha.
 - Eliminar los elementos seleccionador del vector, e insertar uno nuevo, asignado 
   a la raíz del nuevo árbol creado.
*/

// Ordenación mediante Burbuja
void bubble_sort(float * probabilidades, int * codigos, int n) {

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

// Generar un árbol de codificación Huffman
void construyeHuffman(char *codigos, float * probabilidades, int hf[64][4], int & tree_size){

    const int TAMALFABETO = tree_size;

    int orden[TAMALFABETO]; //vector que guarda las posiciones de los códigos
    //char *orden = new char[TAMALFABETO];

    for (int i = 0; i < TAMALFABETO; i++){
        orden[i] = i;
    }

    // Inicializamos los nodos raiz. Exceptuando la información 
    // del padre que aún no la conocemos:
    for(int i = 0; i < TAMALFABETO;  i++){
        hf[i][0] = codigos[i];
        hf[i][1] = -1;
        hf[i][2] = -1;
    }

    for(int i = TAMALFABETO; i < 64; i++){
        hf[i][0] = '_';
    }

    //Definimos las variables para el tamaño del arbol y para el tamaño
    // del vector de orden:
    tree_size = TAMALFABETO;
    int tam_orden = TAMALFABETO;

    // comenzamos a rellenar el arbol mediante Huffman hasta 
    // que tam_orden sea igual a 1, es decir, hasta que lleguemos a la raiz:
    while(tam_orden != 1){

        //Sumamos la probabilidad de los dos elementos con menor probabilidades:
        probabilidades[tam_orden-2]=probabilidades[tam_orden - 2]+ probabilidades[tam_orden-1];

        //Asignamos al nuevo nodo generado sus dos hijos:
        hf[tree_size][1] = orden[tam_orden-2];
        hf[tree_size][2] = orden[tam_orden-1];

        //Ahora asignamos a los dos nodos hijos su nuevo padre:
        hf[ orden[tam_orden-2] ][3] = tree_size;
        hf[ orden[tam_orden-1] ][3] = tree_size;
        
        // Modificamos el vector orden
        orden[tam_orden-2]= tree_size;

        //reducimos el tamaño del vector orden:
        tam_orden--;

        //En caso de que hayamos terminado, indicamos en el nodo que este es la raiz:
        if(tam_orden == 1){
            hf[tree_size][3] = -1;
            //int raiz = hf[tree_size][3];
        }

        //Aumentamos el tamaño del arbol:
        tree_size++;

        //Reordenamos el vector de probabilidades y el de orden:
        bubble_sort(probabilidades, orden, tam_orden);
    }

    cout << endl;
}

// -------------------------------------------------------------------------------- //

// Codificar un mensaje con el árbol de Huffman
void codificarHuffman(char * cadena, int hf[16][4], bool * &codificado, int tree_size){

    unsigned short c;
    int tam;
    char simbolo;
    int pos;
    int padre;
    codificado = new bool[20];
    int contador;

    //Obtenemos el tamaño de la cadena
    int n = strlen(cadena);
    cadena[n] = '*';

    for (int i=0;i<=n; i++){
        simbolo = cadena[i];

        // Buscar símbolo en hf
        pos = -1;
        for (int j=0; j<tree_size and pos==-1; j++){
            if (hf[j][0] == simbolo){
                pos = j;
            }
        }

        contador = 0;

        while (hf[pos][3] != -1){
            int padre = hf[pos][3];

            if (pos == hf[padre][1]){ // hijo izquierda // es un cero
                codificado[contador] = false;
                contador++;

            } else { // hijo derecha // es un uno
                codificado[contador] = true;
                contador++;
            }

            pos = padre;
        }

        // Enviar () --> sendLaserBit
        for (int j=contador-1; j>=0; j--){
            cout << (int)codificado[j];
        }

        cout << " ";     
    }
    
    for(int i=0; i<contador; i++,contador--){
        bool aux = codificado[i];
        codificado[i] = codificado[contador];
        codificado[contador] = aux;
    }
}

// -------------------------------------------------------------------------------- //

// Decodificar una secuencia de bits con el ábrol de Huffman
void decodificarHuffman(char *codificado, int hf[64][4], int tree_size){

    int pos_dec = -1;
    int contador_dec = 0;
    char mensaje[100];
    bool recibido ;
    char letra = '\0';
    char bufferSalida[101];
    int utilbufferSalida;
    int poscodificado = 0;
    
    // Decodificado mensaje
    utilbufferSalida=0;

    while (letra != '*'){

        pos_dec = tree_size-1; // raíz
        letra = '\0';

        // Decodificado bit a bit
        while (letra=='\0') {
            
            // Simulación de recvLaserBit
            recibido = ((char)(codificado[poscodificado]))=='1';
            poscodificado++;

            // es hijo izquierda
            if (!recibido){
                pos_dec = hf[pos_dec][1];
            } else { // es hijo derecha
                pos_dec = hf[pos_dec][2];
            }

            if (hf[pos_dec][1] == -1 and hf[pos_dec][2] == -1){
                // nodo hoja y decodificamos
                letra = hf[pos_dec][0];
                bufferSalida[utilbufferSalida] = letra;
                utilbufferSalida++;

                pos_dec = tree_size-1; // raíz
            }
        }
    }

    // Enviar usb
    bufferSalida[utilbufferSalida-1] = '\0';
    
    for (int i= 0; i<utilbufferSalida;i++)
        cout << bufferSalida[i];
    
    cout << endl;
}
