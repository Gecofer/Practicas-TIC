/*
AUTORES:
    - Gema Correa Fernandez
    - Samuel Cardenete Rodríguez
    - Pablo Parra Garófano
*/

#define F_CPU 16000000UL

//hola
#include <avr/io.h>
#include <util/delay.h>

// Tiempo a dormir en microsegundos
#define DELAY_US 500

int main(void){

    unsigned char dato; // dato a leer desde el sensor
    bool currentLEDstate = false; // Estado actual del LED: encendido o apagado
    
    // Ponemos el PIN 12 de la placa como salida
    DDRB |= 0b00010000;
    
    // Ponemos el PIN 8 de la placa como entrada
    DDRB &= 0b11111110;
    
    // Comenzamos con el LED apagadp
    PORTB &= ~_BV(PORTB4);
    currentLEDstate = false;
    
    while (1) {

        // Cogemos que hay en el pin 8 como entrada
        dato = PINB & 0x01;
        
        // Si el Pin 8 > 0 (hay luz), entonces encendemos el LED
        if (dato > 0 && !currentLEDstate){
            PORTB |= _BV(PORTB4);
            currentLEDstate = true;
        }
        
        // en otro caso, lo apagamos
        else if (dato == 0 && currentLEDstate){
            PORTB &= ~_BV(PORTB4);
            currentLEDstate = false;
        }
        
        // Dormimos
        _delay_us(DELAY_US);
    }
    
    return 0;
    
}