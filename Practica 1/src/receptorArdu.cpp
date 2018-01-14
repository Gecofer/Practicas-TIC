/*
AUTORES:
    - Gema Correa Fernandez
    - Samuel Cardenete Rodríguez
    - Pablo Parra Garófano
*/

#define UART_BAUD_RATE 9600

#include <ticcommardu.h>
#include <avr/interrupt.h>
#include <uart.h>
#include <unistd.h>

#define DEVICE "/dev/cu.usbmodem1411"


int main(void){
    unsigned char dato; // dato a leer desde el fotoreceptor
    char cadena[101];
    unsigned int n = 0;
    
    // Inicialización del puerto UART con la velocidad en bausidos del puerto
    // y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    
    sei();
    
    // Inicializamos el fotorreceptor
    initLaserReceiver();
    
    while(1){
        n = 0;
        
        for (int i=0; i<100;i++){
            recvLaserBit(dato);
            
            if (dato == LASER_DOT)
                cadena[n] = '0';
            
            else if (dato == LASER_DASH)
                cadena[n] = '1';
            
            else
                cadena[n] = '?';
            
            n++;
        }
        
        // enviamos el mensaje al PC
        cadena[n] = '\0';
        arduSendUSB(cadena);
    }
    
    return 0;
    
}
