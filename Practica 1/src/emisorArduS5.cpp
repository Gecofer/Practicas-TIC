#define UART_BAUD_RATE 9600


#include <ticcommardu.h>
#include <util/delay.h>
#include <arducodif.h>
#include <uart.h>
#include <unistd.h>
#include <avr/interrupt.h>
#include <string.h>

/*
Lea desde USB cadenas de caracteres que se envían desde un PC. Se asume que el tamaño
máximo de cada cadena recibida será de 100 bytes útiles.

Codifique la cadena en código Morse, utilizando las funciones de la biblioteca previamente
desarrollada <arducodif.h>.

Envíe cada símbolo codificado por láser, utilizando la biblioteca previamente desarrollada
<ticcommardu.h>.
*/

int main(){

	int fd; // Descriptor de fichero del puerto USB
	char codif[101]; // Buffer de codif
	unsigned char nutil [101];

	char entrada[101]; // Entrada

	// inicialiar puerto UART
	
	// Inicialización del puerto UART con la velocidad en bausios del puerto
    // y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    
    // Interrupciones
    sei();


	initLaserEmitter();


	char datos[101];
	DDRB|= 0X02;

	PORTB&= ~0X02;

	while(1){

		// Recibimos el mensaje
		entrada[0] = '\0';
		arduReceiveUSB(entrada);

		if (strlen(entrada)>0){

			/*
			// Recorremos el mensaje
			for (int i = 0; i < strlen(entrada); i++){
				codificaSimbolo(entrada[i], codif[i], nutil);
			}
			*/

			codificador(entrada, strlen(entrada), codif, nutil);
			int tam= strlen(entrada);
			for (int i = 0; i < tam; i++){
				unsigned char byte = codif[i];
				unsigned char util_simb = nutil[i];
				unsigned char pos =1;
				for(int j = 0; j< util_simb ; j++){
					if((byte&pos)>0){
						sendLaserBit(LASER_DASH);
					}
					else
						sendLaserBit(LASER_DOT);

					pos *= 2;

				}

				sendLaserBit(LASER_NONE);
			}

			sendLaserBit(LASER_NONE);

			arduSendUSB(entrada);			
	    }

	    

	}

	return 0;
}