/*
AUTORES:
	- Gema Correa Fernandez
	- Samuel Cardenete Rodríguez
	- Pablo Parra Garófano
*/

#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;

#define USBPORT "/dev/cu.usbmodem1411"

int main(int argc, char * argv[]){

	int fd; // Descriptor de fichero del puerto USB
	char buf[129]; // Buffer de salida

	// Inicializamos puerto
	fd = InicializarUSB(USBPORT);

	if (fd == -1){
		cout << "Error inicializando puerto" << USBPORT << endl;
		return 0;
	}

	// Bucle principal
	while(1){

		if (receiveUSB(fd, buf)){
			cout << "Mensaje recibido: "<< buf << endl;
		} else {
			cout << "\tERROR RECIBIENDO DATOS\n\n";
			close(fd);
			return 0;
		}
	}

	// Cerrramos el puerto USB
	close(fd);
	return 0;
}