/*
AUTORES:
  - Gema Correa Fernandez
  - Samuel Cardenete Rodríguez
  - Pablo Parra Garófano
*/

#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;
 
// Puerto de comunicaciones con arduino
/* MODIFICAR EL PUERTO CON AQUEL DONDE SE VAYA A CONECTAR ARDUINO */
#define DEVICE "/dev/cu.usbmodem1411"


int main(int argc, char *argv[]) {

  int fd;               // Descriptor de puerto del puerto USB
  char *buf = argv[1];  // Buffer de salida. Tamaño máximo de 128 caracteres
  int ndata;            // Número de datos en el buffer
  int aux;              // Variable auxiliar

  // Se comprueba si se ha recibido la orden por parámetro
  if (argc != 2) {

    cout << "\nError al ejecutar el programa...";
    cout << "\nUso: " << argv[0] << " [On|Off]\n\n";

    exit(-1);

  }

  // Inicializamos puerto
	fd = InicializarUSB(DEVICE);
  if(fd < 0){
    cout << "Error inicializando el puerto" << DEVICE << endl;
    return 0;
  }

  ndata = strlen(buf); // Tamaño del buffer de salida

  if(ndata >0){ // Enviamos si hay algo
    aux = write(fd, buf, ndata+1);
    tcflush(fd, TCIFLUSH);
    cout << "Bytes enviados" << aux << "/" <<ndata << endl;

    // Comprobamos errores en el envío
    if(aux < ndata){
      cout << "Error el buffer tiene "<< ndata << " bytes pero se enciaron " << aux << endl;
      ndata = 0;
    }

    // Si se envio algun dato esperamos respuesta de Arduino
    if( aux > 0){

      unsigned int n = 0;

      do {
        
        aux = read(fd, buf+n, 128);
        n += aux;
      
      } while (buf[n-1] != '\0');

      if(aux > 0){
        cout << "\t Mensaje: "<< buf << endl<< endl;
      }
      else 
        cout<< "\tERROR RECIBIENDO DATOS";
    }
  }

  // Cerramos el puerto USB
	CerrarUSB(fd);
  cout <<"\nFin del programa.\n\n";
  
  return 0;
}




