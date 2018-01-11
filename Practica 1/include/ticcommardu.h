#ifndef __TICCOMMARDU__

#define __TICCOMMARDU__

// Ciclo de reloj del procesador: 16MHz
#define F_CPU 16000000UL


// Tiempo de ciclo para comunicaciones por láser, en milisegundos
#define UMBRAL_U 9

// Tiempo de muestreo
#define SAMPLE_PERIOD (UMBRAL_U/3)


// Constante que representa una ráfaga corta (puntos)
#define LASER_DOT 0

// Constante que representa una ráfaga larga (raya)
#define LASER_DASH 1

// Constante que representa ninguna ráfaga
#define LASER_NONE 2


// Constante que representa el que laser está encendido
#define LASER_HIGH 1

// Constante que representa el que laser está apagado
#define LASER_LOW 0


/**
 * Inicializa el emisor de láser, apagándolo
 */
void initLaserEmitter();


/**
 * Función para enviar por láser un símbolo.
 *
 * Entradas: 
 *  what: Qué se envía. Puede ser uno de los valores siguientes: 
 *    LASER_DOT para enviar una ráfaga corta, 
 *    LASER_DASH para enviar una ráfaga larga
 *    LASER_NONE para pasar un ciclo sin enviar nada
 *
 */
void sendLaserBit(const unsigned char what);


/**
 * Función para enviar por láser un símbolo.
 *
 * Entradas: 
 *  what: Qué se envía. Puede ser uno de los valores siguientes: 
 *    LASER_HIGH para enviar un 1 
 *    LASER_LOW para enviar un 0
 *
 */
void sendLaserBit2(const unsigned char what);


/**
 * Inicializa el receptor de láser
 */
void initLaserReceiver();


/**
 * Función para recibir un símbolo desde el fotorreceptor de láser.
 *
 * Entradas: Ninguna
 *
 * salidas
 *  what: Qué se ha recibido. Puede ser uno de los valores siguientes: 
 *    LASER_DOT para recibir una ráfaga corta, 
 *    LASER_DASH para recibir una ráfaga larga
 *    LASER_NONE para indicar que no se ha recibido nada
 *
 */
void recvLaserBit(unsigned char & what);


/**
 * Función para recibir un símbolo desde el fotorreceptor de láser.
 *
 * Entradas: Ninguna
 *
 * salidas
 *  what: Qué se ha recibido. Puede ser uno de los valores siguientes: 
 *    LASER_HIGH para recibir un 1, 
 *    LASER_DASH para recibir un 0
 */
void recvLaserBit2(unsigned char & what);


/**
 * Función para enviar un mensaje por USB a PC
 * 
 * Entradas: 
 *  data: Cadena de datos a enviar.
 * 
 * Salidas: true si los datos se enviaron con éxito, false en otro caso
 */
bool arduSendUSB(const char *data);  


/**
 * Función para recibir un mensaje por USB desde PC
 * 
 * Entradas: Ninguna
 * 
 * Salidas: true si los datos se enviaron con éxito, false en otro caso
 *  en el parámetro data: Cadena de caracteres recibida
 */
bool arduReceiveUSB (char *data);


/**
 * Función para enviar un byte por USB a PC
 * 
 * Entradas: 
 *  data: caracter a enviar.
 * 
 * Salidas: true si los datos se enviaron con éxito, false en otro caso
 */
bool arduSendByteUSB(unsigned char data);  


/**
 * Función para recibir un mensaje por USB desde PC
 * 
 * Entradas: Ninguna
 * 
 * Salidas: true si los datos se enviaron con éxito, false en otro caso
 *  en el parámetro data: Byte recibido
 */
bool arduReceiveByteUSB (unsigned char &data);


#endif
