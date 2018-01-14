/*
AUTORES:
    - Gema Correa Fernandez
    - Samuel Cardenete Rodríguez
    - Pablo Parra Garófano
*/

#include <ticcommpc.h>
#include <iostream>

using namespace std;

// Puerto de comunicaciones con arduino
#define COMMPORTEMISOR "/dev/cu.usbmodem1461"
#define COMMPORTRECEPTOR "/dev/cu.usbmodem1441"

// Programa principal
int main(int argc, char *argv[]){

    int fd;         // Descriptor de fichero del puerto USB
    char buf[129];  // Buffer de salida. Tamaño máximo de 128 caracteres.
    int puerto = 0; // Puerto de Arduino

    // Se lee el argumento recibido para cambiar el puerto del Arduino
    if(argc == 2 && atoi(argv[1]) == 1){
        puerto = 1;
    }

    // Inicializamos puerto
    if(puerto == 0){
      fd = InicializarUSB(COMMPORTEMISOR);
    } else {
      fd = InicializarUSB(COMMPORTRECEPTOR);
    }

    if(fd==-1){

        if(puerto == 0){
            cout << "Error inicializando puerto " << COMMPORTEMISOR << endl;
        } else{
            cout << "Error inicializando puerto " << COMMPORTRECEPTOR << endl;
        }

        return 0;
    }

    cout << "Leemos...\n" << endl;

    // Bucle principal
    while (true){

        // Se leen datos del USB
        if(receiveUSB(fd, buf)){

            if(atoi(buf) == 0){
                cout << "Sin luz, enciende las velas" << endl;
            } else if(atoi(buf) == 1){
                cout << "Hace sol, vamos a salir" << endl;
            }
        }

    }

    // Se cierra el puerto USB
    CerrarUSB(fd);
    return 0;
}
