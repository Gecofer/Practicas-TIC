/*
AUTORES:
  - Gema Correa Fernandez
  - Samuel Cardenete Rodríguez
  - Pablo Parra Garófano
*/
// Ciclo de reloj del procesador: 16MHz
#define F_CPU 16000000UL

// Velocidad (en baudios) de las comunicaciones serie
#define UART_BAUD_RATE 9600

#define DELAY_MS 1000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <uart.h>
#include <string.h>

#include "ticcommardu.cpp"

int main(void) {

  // Se establece como entrada el pin 12
  DDRB |= 0b00010000;

  // Byte de datos recibido por puerto serie
  // El byte menos significativo es el dato
  // El segundo byte menos significativo contiene 
  // información de error
  unsigned int c;

  bool leido = true;

  // Inicialización del puerto UART con la velocidad 
  // en baudios del puerto, y la velocidad del procesador    
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );

  // Activación de las interrupciones hardware para
  // control del puerto serie  
	sei();
    
  while (1) {

    char mensaje[128] = "";
    arduReceiveUSB(mensaje);

    if (strcmp(mensaje, "On") == 0) {
      leido = true;      
      arduSendUSB("Led encendido");
            
    } else if (strcmp(mensaje, "Off") == 0) {
      leido = false;      
      arduSendUSB("Led apagado");
    
    } else {      
      arduSendUSB("No entiendo la orden");        
    }

    if (leido) {
      // Se manda la señal de voltaje alto al pin 12 del puerto B
      PORTB |= 0b00010000;
      _delay_ms(DELAY_MS);

    } else {
      // Se manda la señal de voltaje bajo al pin 0 del puerto B
      PORTB &= 0b00000000;
      _delay_ms(DELAY_MS);
    }
  }

  return 0;
}
