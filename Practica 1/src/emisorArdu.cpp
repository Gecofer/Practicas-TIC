/*
AUTORES:
	- Gema Correa Fernandez
	- Samuel Cardenete Rodríguez
	- Pablo Parra Garófano
*/

#include <ticcommardu.h>
#include <util/delay.h>
#include <arducodif.h>

int main(){
	initLaserEmitter();

	while(1){

		char datos[101];

		if (!arduReceiveUSB(datos)){
			int i =0;
			
			char c;
			do{
				c = datos[i];
				//sendSymbol(c);
			}while(c != '\0');
			
			

			sendLaserBit(LASER_DOT);
			sendLaserBit(LASER_DOT);
			sendLaserBit(LASER_DOT);

			sendLaserBit(LASER_NONE);

			sendLaserBit(LASER_DASH);
			sendLaserBit(LASER_DASH);

			sendLaserBit(LASER_NONE);

			sendLaserBit(LASER_DOT);
			sendLaserBit(LASER_DOT);
			sendLaserBit(LASER_DOT);

			sendLaserBit(LASER_NONE);
		}




	}


	return 0;
}