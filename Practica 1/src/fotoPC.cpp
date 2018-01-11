#include <ticcommpc.h>
#include <iostream>

using namespace std;

// Puerto de comunicaciones con arduino
//#define USBPORT0 "/dev/ttyACM0"
//#define USBPORT1 "/dev/ttyACM1"
#define USBPORT0 "/dev/ttyUSB0"
#define USBPORT1 "/dev/ttyUSB1"

// Programa principal
int main(int argc, char *argv[]){

    int port = 0;

    // Se lee el argumento recibido para cambiar el puerto del Arduino
    if(argc == 2 && atoi(argv[1]) == 1){
        port = 1;
    }

    // Descriptor de fichero del puerto USB
    int fd;

    // Buffer de salida. Tamaño máximo de 128 caracteres.
    char buf[129];

    // Inicializamos puerto
    if(port == 0){
      fd = InicializarUSB(USBPORT0);
    } else{
      fd = InicializarUSB(USBPORT1);
    }

    if(fd==-1){

        if(port == 0){
            cout << "Error inicializando puerto " << USBPORT0 << endl;
        } else{
            cout << "Error inicializando puerto " << USBPORT1 << endl;
        }

        return 0;

    }

    cout << "Comenzando a leer...\n" << endl;

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
