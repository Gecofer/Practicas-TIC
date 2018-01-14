/*
AUTORES:
  - Gema Correa Fernandez
  - Samuel Cardenete Rodríguez
  - Pablo Parra Garófano
*/


#include <ticcommardu.h>
#include <uart.h>
#include <string.h>
#include <util/delay.h>


void initLaserEmitter() {


  // Asumimos que está en el pin 12 de Arduino.
  DDRB |= _BV(DDB4);

  // Ponemos salida a baja
  PORTB &= ~_BV(DDB4);
}


void sendLaserBit(const unsigned char what) {

  // Ponemos salida a alta si hay que enviar ráfaga
  if (what != LASER_NONE)
    PORTB |= _BV(DDB4);

  // Esperamos el tiempo de ciclo
  if (what != LASER_DASH)
    _delay_ms(UMBRAL_U);
  else
    _delay_ms(2*UMBRAL_U);

  // Ponemos salida a baja
  PORTB &= ~_BV(DDB4);

  // Y esperamos un ciclo
  if (what != LASER_NONE)
    _delay_ms(UMBRAL_U);
}


void sendLaserBit2(const unsigned char what) {

  // Ponemos salida a alta si hay que enviar 1
  if (what == LASER_HIGH)
    PORTB |= _BV(DDB4);
  else // O ponemos a baja si se envía 0
    PORTB &= ~_BV(DDB4);

  // Esperamos el tiempo de ciclo
  _delay_ms(UMBRAL_U);
}


void initLaserReceiver(){

  // Asumimos que está en el pin 8 de Arduino.
  DDRB &= ~_BV(DDB0);
}


void recvLaserBit(unsigned char & what) {

  unsigned char cBajo=0; // Contador de veces que se detecta voltaje bajo
  unsigned char cAlto=0; // Contador de veces que se detecta voltaje alto
  unsigned char dato; // Dato a medir

  // Inicialmente suponemos que está en bajo
  //  Comprobamos si es mensaje LASER_NONE
  do {

    // Asumimos que está en el PIN 8
    dato= PINB & 0x01;

    if (dato>0)
      cAlto++;
    else
      cBajo++;

    if (cBajo>3) {
      what= LASER_NONE;
      return;
    }
    
    // Esperamos al siguiente muestreo
    _delay_ms( SAMPLE_PERIOD );

  } while (dato == 0);


  // Si llegamos aquí, está llegando una ráfaga
  //  Comprobamos si es ráfaga corta o larga
  do {

    // Asumimos que está en el PIN 8
    dato= PINB & 0x01;

    if (dato>0)
      cAlto++;
    
    // Esperamos al siguiente muestreo
    _delay_ms( SAMPLE_PERIOD );

  } while (dato == 1);

  // Si hemos muestreado más de 3 veces lo mismo, entonces es raya
  if (cAlto>3)
    what= LASER_DASH;

  else // En otro caso, es un punto
    what= LASER_DOT;

}



void recvLaserBit2(unsigned char & what) {

  unsigned char cBajo=0; // Contador de veces que se detecta voltaje bajo
  unsigned char cAlto=0; // Contador de veces que se detecta voltaje alto
  unsigned char tiempo=0; // Tiempo midiendo
  unsigned char dato; // Dato a medir
  unsigned char inicial= 3; // Dato a medir

  // Inicialmente suponemos que está en bajo
  //  Comprobamos si es mensaje LASER_NONE

  // Pasamos un ciclo midiendo
	while (cAlto <2 && cBajo<2) {
		tiempo= 0;

	  // Asumimos que está en el PIN 8
	  inicial= PINB & 0x01;
		dato= inicial;

	  if (dato>0) // Miramos si está en alta o en baja
	    cAlto++;
	  else
	    cBajo++;

	  // Esperamos el periodo de muestreo
	  _delay_ms( SAMPLE_PERIOD );

	  // Y aumentamos el tiempo que hemos estado en la función
	  tiempo+= SAMPLE_PERIOD;

		while (tiempo < UMBRAL_U && dato==inicial) {

		  // Asumimos que está en el PIN 8
		  dato= PINB & 0x01;

		  if (dato>0) // Miramos si está en alta o en baja
		    cAlto++;
		  else
		    cBajo++;

		  // Esperamos el periodo de muestreo
		  _delay_ms( SAMPLE_PERIOD );

		  // Y aumentamos el tiempo que hemos estado en la función
		  tiempo+= SAMPLE_PERIOD;
		}
	}

  // Si hemos muestreado más altas que bajas, devolvemos LASER_HIGH
  if (cAlto>cBajo)
    what= LASER_HIGH;

  else // En otro caso, es un LASER_LOW
    what= LASER_LOW;
}




bool arduSendUSB(const char *data) {

  int ndata= strlen(data)+1; // Tamaño del buffer de salida

  for (int i= 0; i<ndata; i++)
    uart_putc(data[i]);
  return true;
}



bool arduReceiveUSB (char *data) {

  int posbuf= 0;
  data[0]= '\n';
  int c;

  while (data[posbuf-1]!='\0' || posbuf==0) {
 
    // Recogemos byte desde puerto UART
    c = uart_getc();

    if ( c & UART_FRAME_ERROR || c & UART_OVERRUN_ERROR ||  c & UART_BUFFER_OVERFLOW ) {
      return false;
    
    // Todo ok, insertamos el caracter en el buffer
    } else if (!( c & UART_NO_DATA )) {

      data[posbuf]= (char) (c);
      posbuf++;
    }
  }
  return true;
}


bool arduSendByteUSB(unsigned char data) {

	uart_putc(data);

	return true;
}


bool arduReceiveByteUSB (unsigned char &data) {

		int c = uart_getc();

    if ( c & UART_FRAME_ERROR || c & UART_OVERRUN_ERROR ||  c & UART_BUFFER_OVERFLOW ) {
      return false;
    
    // Todo ok, insertamos el caracter en el buffer
    } else if (!( c & UART_NO_DATA )) {

      data= (unsigned char)c;
			return true;
    }

		return false;
}



