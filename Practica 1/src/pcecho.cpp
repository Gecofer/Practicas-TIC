#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;
 
// Puerto de comunicaciones con arduino

/* MODIFICAR EL PUERTO CON AQUEL DONDE SE VAYA A CONECTAR ARDUINO */
#define DEVICE "/dev/cu.usbmodem1421"


 
int main(int argc, char *argv[]) {

  int fd; // Descriptor de puerto del puerto USB
  char buf[129]; // Buffer de salida. Tamaño máximo de 128 caracteres
  int ndata; // Número de datos en el buffer
  int aux;
  cout << 1;

  // Inicializamos puerto

	fd = InicializarUSB(DEVICE);
  if(fd < 0){
    cout << "Error inicializando el puerto" << DEVICE << endl;
    return 0;
  }

  // Bucle hasta que salgamos (cuando no introduzcamos nada)
  do {

		cout<< "Escriba algo para enviar a arduino:";
    cin.getline(buf, 128);

    ndata = strlen(buf);

    if(ndata >0){
      aux = write(fd, buf, ndata);
      tcflush(fd, TCIFLUSH);
      cout << "Bytes enviados" << aux << "/" <<ndata << endl;

      if(aux < ndata){
        cout << "Error el buffer tiene "<< ndata << " bytes pero se enciaron " << aux << endl;
        ndata = 0;
      }

      //si se envio algun dato esperamos respuesta:
      if( aux > 0){
        aux = read(fd, buf, 128);
        if(aux > 0){
          cout << "\t Mensaje: "<< buf << endl<< endl;
        }
        else 
          cout<< "\tERROR RECIBIENDO DATOS";
      }
    }

      

  // Se sale si no enviamos ningún caracter
  } while (ndata > 0);


  // Cerramos el puerto USB

	CerrarUSB(fd);
  cout <<"\nFin del programa.\n\n";
  return 0;
}




