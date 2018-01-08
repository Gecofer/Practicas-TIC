#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;


#define USBPORT "/dev/cu.usbmodem1411"

int main(int argc, char * argv[]){

	int fd; // Descriptor de fichero del puerto USB
	char buf[101]; // Buffer de salida
	char resultado[10];

	// Inicializamos puerto
	fd = InicializarUSB(USBPORT);

	if (fd == -1){
		cout << "Error inicializando puerto" << USBPORT << endl;
		return 0;
	}

	// Bucle principal
	while(1){
		cout<< "Escriba algo para enviar a arduino:";
   		cin.getline(buf, 101);

   		sendUSB(fd, buf);


		while (!receiveUSB(fd, resultado)){}
			
		cout << "Mensaje recibido: "<< resultado << endl;
	}

	// Cerrramos el puerto USB
	close(fd);
	return 0;
}