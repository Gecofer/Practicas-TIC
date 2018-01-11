
// Ciclo de reloj del procesador: 16MHz
#define F_CPU 16000000UL

// Velocidad (en baudios) de las comunicaciones serie
#define UART_BAUD_RATE 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <uart.h>
  

int main(void) {

  // Byte de datos recibido por puerto serie
  // El byte menos significativo es el dato
  // El segundo byte menos significativo contiene 
  // información de error
  unsigned int c;

  // Inicialización del puerto UART con la velocidad 
  // en baudios del puerto, y la velocidad del procesador    
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU) );


  // Activación de las interrupciones hardware para
  // control del puerto serie  
	sei();
    

  while (1) {

		// recogemos un byte:
    c = uart_getc();

    // flag sin datos:
    if(c & UART_NO_DATA){
      _delay_ms(1);
    }
    else if(c & UART_FRAME_ERROR){  // error recibiendo la trama
      uart_puts_P("ERROR: recibiendo trama \n");
    }
    else if(c & UART_OVERRUN_ERROR){// demasiado rapido
      uart_puts_P("ERROR: no pudo leer dato antes de recibir el siguiente\n");
    }
    else if(c & UART_BUFFER_OVERFLOW){// no estamos leyendo tan rapido como nos envian
      uart_puts_P("ERROR: el buffer esta lleno \n");

    }else{ // TODO VA BIEN, RESPONDEMOS CON EL MISMO CARACTER:
      uart_putc((unsigned char)c);
    }

  }

  return 0;   
}
