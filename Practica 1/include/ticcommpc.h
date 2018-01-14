/*
AUTORES:
	- Gema Correa Fernandez
	- Samuel Cardenete Rodríguez
	- Pablo Parra Garófano
*/


#ifndef __TICCOMMPC__

#define __TICCOMMPC__


/**
 * Función para inicializar el puerto USB
 * 
 * Entradas: Una cadena de caracteres con el puerto USB (ejemplo: "/dev/ttyACM0", "/dev/ttyUSB0", "COM3", etc.)
 * 
 * Salidas: Un descriptor de puerto correspondiente al puerto 
 * de comunicaciones si hubo éxito (valor 0 o mayor). Un código de error (menor que 0) en caso contrario:
 * 	- Valor >=0 si todo se inicializó correctamente. Se corresponde con el código del puerto abierto
 * 	- Valor -1 si hubo error al abrir el puerto.
 * 	- Valor -2 si no se conoce el puerto de entrada dado en "portname"
 */
int InicializarUSB(const char *portname);


/**
 * Paraliza la ejecución del programa por unos milisegundos dados por argumento.
 */
int Dormir(int ms);


/**
 * Cierra las comunicaciones por el puerto USB para el descriptor dado por argumento
 */
void CerrarUSB(int &pd);


/**
 * Función para enviar una cadena de caracteres por un descriptor de puerto USB
 * @param pd Descriptor del puerto USB a utilizar
 * @param Buffer a enviar
 */
bool sendUSB(int &pd, char *data);


/**
 * Función para recibir datos desde USB. La función bloquea la ejecución del programa hasta que
 *  se ha recibido al menos 1 byte por USB.
 * @param pd Descriptor del puerto USB a utilizar para recibir datos.
 * @param data Buffer de salida. Debe contener memoria para almacenar los datos que se recibirán.
 */
bool receiveUSB (int &fd, char *data);


/**
 * Función para enviar un byte  por un descriptor de puerto USB
 * @param pd Descriptor del puerto USB a utilizar
 * @param Byte a enviar
 */
bool sendByteUSB(int &pd, unsigned char data);


/**
 * Función para recibir un byte desde USB. La función bloquea la ejecución del programa hasta que
 *  se ha recibido 1 byte por USB.
 * @param pd Descriptor del puerto USB a utilizar para recibir datos.
 * @param data Byte de salida.
 */
bool receiveByteUSB (int &fd, unsigned char &data);

#endif


