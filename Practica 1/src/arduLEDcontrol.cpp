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

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <uart.h>
#include <string.h>
  

int main(void) {

  // Se establece como entrada el pin 12
  DDRB |= 0b00010000;

  // Byte de datos recibido por puerto serie
  // El byte menos significativo es el dato
  // El segundo byte menos significativo contiene 
  // información de error
  unsigned int c;

  bool leido = true;
  unsigned int contador = 0;
    
  char mensaje[129] = "";  
  char mensajeOn[129] = "Led encendido\0";
  char mensajeOff[129] = "Led apagado\0";
  char mensajeError[129] = "No entiendo la orden\0";

  // Inicialización del puerto UART con la velocidad 
  // en baudios del puerto, y la velocidad del procesador    
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );

  // Activación de las interrupciones hardware para
  // control del puerto serie  
	sei();
    
  while(1){
        
    do {
        
      // Se recoge el byte desde el puerto UART
      c = uart_getc();

      // Flag sin datos activado. Se duerme
      if (c & UART_NO_DATA) {
        _delay_ms(1);

      // Error de recepción de la trama de datos. Se envía el mensaje
      } else if (c & UART_FRAME_ERROR) {
        uart_puts_P("Error recibiendo trama.\n");

      // Error de recepción de dato más rápido de lo que se pudo leer el
      // anterior
      } else if (c & UART_OVERRUN_ERROR) {
        uart_puts_P("Error: La interrupción no pudo leer el dato antes de recibir el siguiente.\n");

      // Error de recepción: Buffer lleno. No estamos leyendo tan rápido como
      // nos envían
      } else if (c & UART_BUFFER_OVERFLOW) {
        uart_puts_P("Error: El buffer está lleno. No se puede leer tan rápido como se envía\n");

      // Todo ok. Se responde con el mismo carácter
      } else {
        mensaje[contador] = (unsigned char)c;
        contador++;
      }
            
    } while(c!='\0');
              
    // Se comprueba qué se debe hacer con el led
    if (strcmp(mensaje, "On") == 0) {
      leido = true;      
      strcpy(mensaje, mensajeOn);
            
    } else if (strcmp(mensaje, "Off") == 0) {
      leido = false;      
      strcpy(mensaje, mensajeOff);

    } else {      
      strcpy(mensaje, mensajeError);        
    }

    // Se manda señal de voltaje alto al pin 12 del puerto B
    if (leido) {
      PORTB |= 0b00010000;
    
    // Se manda señal de voltaje bajo al pin 0 del puerto B
    } else {      
      PORTB &= 0b11101111;        
    }
        
    unsigned int size = strlen(mensaje);
    contador = 0;

    // Se recorre la cadena completa
    while (contador <= size) {
      uart_putc(mensaje[contador]); // Se envía el carácter
      contador++;
    }

  }

  return 0;

}
