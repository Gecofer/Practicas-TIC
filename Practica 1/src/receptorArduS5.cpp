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
#include <string.h>
#include <arducodif.h>

#define DEVICE "/dev/cu.usbmodem1411"

/*
Debe tener una variable de estado estado, capaz de diferenciar entre el estado “Recibiendo” y “En espera” 
(ver Seminario 1). Inicialmente, se debe encontrar “En espera”. También debe tener declarados dos buffers, 
uno para recibir datos codificados desde el receptor láser (llamémosle Laser), y otro buffer decodificado 
para almacenar la información recibida por el receptor láser ya decodificada. Ambos buffers deben estar 
inicializados a vacío. A continuación, en un bucle infinito se debe realizar lo siguiente:

 - Leer dato del fotorreceptor láser, mientras no se encuentre en estado “Recibiendo”.
 - Leer un mensaje desde el receptor láser (máximo de 100 bytes útiles), hasta que se 
    vuelva a pasar a estado “En espera” (ver Seminario 1).
 - Decodificar el mensaje.
 - Enviarlo por USB a un PC.
*/


int main(void){

    // Dato a leer desde el fotorreceptor
    unsigned char L; 
    unsigned char asci;
    char cadena[101];
    unsigned int n = 0;
    unsigned char nUtil;
    char codigos[101];
    unsigned char utiles[101];
    unsigned char codigo;
    unsigned char pos;
    
    // Inicialización del puerto UART con la velocidad en bausidos del puerto
    // y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    
    sei();
    
    // Inicializamos el fotorreceptor
    initLaserReceiver();
    bool fin_mensaje = false;
    bool fin_simbolo = false;

    while(1){

        fin_mensaje = false;
        fin_simbolo = false;

        n = 0;

        codigo = 0b00000000;
        pos = 1;
        nUtil = 0;

        // no hacer nada
        do {
            recvLaserBit(L);
        } while (L == LASER_NONE);

        while (!fin_mensaje){

            while (!fin_simbolo){

                if (L == LASER_DASH)
                    codigo |= pos;

                pos <<=1;
                nUtil++;

                recvLaserBit(L);
                
                fin_simbolo = (L == LASER_NONE);
            }

            // decodificar
            // decodificaSimboloMorse(const char ccodif, const unsigned char nUtils, unsigned char & decodif)
            codigos[n]=codigo;
            utiles[n]=nUtil;
            fin_simbolo= false;

            // meter buffer de salida
            //cadena[n] = asci; // caracter decodificado
            n++;

            codigo = 0;
            pos = 1;
            nUtil = 0;

            recvLaserBit(L);

            fin_mensaje = (L == LASER_NONE);
        }

        for (int i = 0; i < n; i++){
            decodificaSimboloMorse(codigos[i], utiles[i], asci);
            cadena[i]=asci;
        }

        cadena[n] = '\0';
       
        arduSendUSB(cadena);
    }
    
    return 0;
}
