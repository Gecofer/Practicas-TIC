#include <ticcommpc.h>
#include <string.h>
#include <stdio.h>

#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) 

// Includes para Linux y MAC
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>


#else


// Includes para Windows
#include<windows.h>

// Total de puertos existentes
#define RS232_PORTNR 16

HANDLE Cport[RS232_PORTNR]; // Variable para control de los puertos

// Puertos asociados a las comunicaciones por USB
const char *comports[RS232_PORTNR]={"\\\\.\\COM1",  "\\\\.\\COM2",  "\\\\.\\COM3",  "\\\\.\\COM4",
                              "\\\\.\\COM5",  "\\\\.\\COM6",  "\\\\.\\COM7",  "\\\\.\\COM8",
                              "\\\\.\\COM9",  "\\\\.\\COM10", "\\\\.\\COM11", "\\\\.\\COM12",
                              "\\\\.\\COM13", "\\\\.\\COM14", "\\\\.\\COM15", "\\\\.\\COM16"};
#endif



// Inicializar el puerto USB en el dispositivo dado por argumento
int InicializarUSB(const char *portname) {

	int USBPORT= -1; // Puerto USB a utilizar. -1 indica que no está asignado

	#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__) 
		
		// IMPLEMENTACION PARA LINUX Y MAC
		struct termios toptions; // Estructura para control del puerto USB
		
		// Abrimos puerto USB para E/S, sin bloqueo del puerto 
		USBPORT= open(portname, O_RDWR | O_NOCTTY);

		if (USBPORT == -1)
			return -1;

		// Cogemos la configuración actual de dispositivos /dev/tty*
		tcgetattr(USBPORT, &toptions);

		// Configuramos baudios para entrada y para salida
		cfsetispeed(&toptions, B9600); // Trabajaremos a 9600 baudios
		cfsetospeed(&toptions, B9600); // Trabajaremos a 9600 baudios

		// Personalizamos opciones
		toptions.c_cflag &= ~PARENB;
		toptions.c_cflag &= ~CSTOPB;
		toptions.c_cflag &= ~CSIZE;
		toptions.c_cflag |= CS8;

		// Sin control del flujo de datos por hardware
		toptions.c_cflag &= ~CRTSCTS;

		// Habilitamos para lectura y sin control de estado
		toptions.c_cflag |= CREAD | CLOCAL;

		// Deshabilitamos control E/S y caracteres de reinicio del puerto
		toptions.c_iflag &= ~(IXON | IXOFF | IXANY);

		// Deshabilitamos entradas canónicasl, echo, caracteres de borrado de linea
		toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

		// Deshabilitamos post-procesamiento de las salidas
		toptions.c_oflag &= ~OPOST;
	
		// Hacemos que devolvamos cada byte según nos llega (tam. buffer llegada)
		toptions.c_cc[VMIN]= 1;

		// Sin espera desde que llegan datos en el puerto hasta que los cogemos
		toptions.c_cc[VTIME]= 0;

		// Establecemos las opciones del puerto
		tcsetattr(USBPORT, TCSANOW, &toptions);

  #else

    // IMPLEMENTACION PARA WINDOWS

		// Modo de apertura del puerto USB. E/S bidireccional serie normal de bytes
		char mode[]={'8','N','1', 0};
		const int BAUD_RATE= 9600; // Velocidad (en baudios) para transmitir por el puerto serie
	
		// Hallamos el código del puerto USB según el dispositivo dado de entrada
		if (strcmp(portname, "COM1") == 0) USBPORT= 0;
		else if (strcmp(portname, "COM2") == 0) USBPORT= 1;
		else if (strcmp(portname, "COM3") == 0) USBPORT= 2;
		else if (strcmp(portname, "COM4") == 0) USBPORT= 3;
		else if (strcmp(portname, "COM5") == 0) USBPORT= 4;
		else if (strcmp(portname, "COM6") == 0) USBPORT= 5;
		else if (strcmp(portname, "COM7") == 0) USBPORT= 6;
		else if (strcmp(portname, "COM8") == 0) USBPORT= 7;
		else if (strcmp(portname, "COM9") == 0) USBPORT= 8;
		else if (strcmp(portname, "COM10") == 0) USBPORT= 9;
		else if (strcmp(portname, "COM11") == 0) USBPORT= 10;
		else if (strcmp(portname, "COM12") == 0) USBPORT= 11;
		else if (strcmp(portname, "COM13") == 0) USBPORT= 12;
		else if (strcmp(portname, "COM14") == 0) USBPORT= 13;
		else if (strcmp(portname, "COM15") == 0) USBPORT= 14;
		else if (strcmp(portname, "COM16") == 0) USBPORT= 15;

		if (USBPORT == -1)
			return -1;



		char mode_str[128];
		switch(BAUD_RATE)
		{
		  case     110 : strcpy(mode_str, "baud=110");
		                 break;
		  case     300 : strcpy(mode_str, "baud=300");
		                 break;
		  case     600 : strcpy(mode_str, "baud=600");
		                 break;
		  case    1200 : strcpy(mode_str, "baud=1200");
		                 break;
		  case    2400 : strcpy(mode_str, "baud=2400");
		                 break;
		  case    4800 : strcpy(mode_str, "baud=4800");
		                 break;
		  case    9600 : strcpy(mode_str, "baud=9600");
		                 break;
		  case   19200 : strcpy(mode_str, "baud=19200");
		                 break;
		  case   38400 : strcpy(mode_str, "baud=38400");
		                 break;
		  case   57600 : strcpy(mode_str, "baud=57600");
		                 break;
		  case  115200 : strcpy(mode_str, "baud=115200");
		                 break;
		  case  128000 : strcpy(mode_str, "baud=128000");
		                 break;
		  case  256000 : strcpy(mode_str, "baud=256000");
		                 break;
		  case  500000 : strcpy(mode_str, "baud=500000");
		                 break;
		  case 1000000 : strcpy(mode_str, "baud=1000000");
		                 break;
		  default      : 
		                 return(-1);
		                 break;
		}

		switch(mode[0])
		{
		  case '8': strcat(mode_str, " data=8");
		            break;
		  case '7': strcat(mode_str, " data=7");
		            break;
		  case '6': strcat(mode_str, " data=6");
		            break;
		  case '5': strcat(mode_str, " data=5");
		            break;
		  default : 
		            return(-1);
		            break;
		}

		switch(mode[1])
		{
		  case 'N':
		  case 'n': strcat(mode_str, " parity=n");
		            break;
		  case 'E':
		  case 'e': strcat(mode_str, " parity=e");
		            break;
		  case 'O':
		  case 'o': strcat(mode_str, " parity=o");
		            break;
		  default : 
		            return(-1);
		            break;
		}

		switch(mode[2])
		{
		  case '1': strcat(mode_str, " stop=1");
		            break;
		  case '2': strcat(mode_str, " stop=2");
		            break;
		  default : 
		            return(-1);
		            break;
		}
		strcat(mode_str, " dtr=on rts=on");

		Cport[USBPORT] = CreateFileA(comports[USBPORT],
				                  GENERIC_READ|GENERIC_WRITE,
				                  0,                          /* no share  */
				                  NULL,                       /* no security */
				                  OPEN_EXISTING,
				                  0,                          /* no threads */
				                  NULL);                      /* no templates */

			if(Cport[USBPORT]==INVALID_HANDLE_VALUE)
			{
				return(-1);
			}

			DCB port_settings;
			memset(&port_settings, 0, sizeof(port_settings));  /* clear the new struct  */
			port_settings.DCBlength = sizeof(port_settings);

			if(!BuildCommDCBA(mode_str, &port_settings))
			{
				CloseHandle(Cport[USBPORT]);
				return(1);
			}

			if(!SetCommState(Cport[USBPORT], &port_settings))
			{
				CloseHandle(Cport[USBPORT]);
				return(1);
			}

			COMMTIMEOUTS Cptimeouts;

			Cptimeouts.ReadIntervalTimeout         = MAXDWORD;
			Cptimeouts.ReadTotalTimeoutMultiplier  = 0;
			Cptimeouts.ReadTotalTimeoutConstant    = 0;
			Cptimeouts.WriteTotalTimeoutMultiplier = 0;
			Cptimeouts.WriteTotalTimeoutConstant   = 0;

			if(!SetCommTimeouts(Cport[USBPORT], &Cptimeouts))
			{
				CloseHandle(Cport[USBPORT]);
				return(1);
			}

	#endif // Fin de la implementación para windows

	Dormir(2000);
	return USBPORT;
}


void CerrarUSB(int &pd) {

	#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)

    // IMPLEMENTACION PARA LINUX Y MAC
		close(pd);

	#else

    // IMPLEMENTACION PARA WINDOWS
		CloseHandle(Cport[pd]);

	#endif

	pd= -1;
}



int Dormir(int ms) {

	#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)

		usleep(1000*ms);  // Dormir 100 ms para linux (microsegundos)

	#else

		Sleep(ms); // Dormir 100 ms para windows

	#endif

	return 0;
}



bool sendUSB(int &pd, char *data) {

	#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)

    // IMPLEMENTACION PARA LINUX Y MAC
		const int ndata= strlen(data)+1;

		// Escribimos en el puerto
		int aux= write(pd, data, ndata);

		tcflush(pd, TCIFLUSH); // Forzamos envío del buffer

		// Damos tiempo a procesar las salidas: 100ms por poner algo.
		Dormir(100);
		
		return aux == ndata;


	#else

    // IMPLEMENTACION PARA WINDOWS

		int n;

		if(WriteFile(Cport[pd], data, strlen(data)+1, (LPDWORD)((void *)&n), NULL))
		{
			// Damos tiempo a procesar las salidas: 100ms por poner algo.
			Dormir(100);
		  return (n==strlen(data)+1);
		}

	  return false;

	#endif

}


bool receiveUSB (int &pd, char *data) {

	#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)

    // IMPLEMENTACION PARA LINUX Y MAC

		// Esperamos a recibir cadena terminada en '\0'
		int n= 0;
		int aux;
		char c= ' ';
		do {
			aux= read(pd, &c, 1);
			if (aux > 0) {

				data[n]= c;
				n++;

			} else
				return false;

		} while (c != '\0');


	#else 

    // IMPLEMENTACION PARA WINDOWS

		int ndata= 0;
		int nbuf= 0;
		bool salir= false;
		while (!salir) {

			ReadFile(Cport[pd], (unsigned char *)data+nbuf, 1, (LPDWORD)((void *)&ndata), NULL);
			if (ndata == 0)
				Dormir(5);
			else {
				if (data[nbuf] == '\0')
					salir= true;
				nbuf+=ndata;
			}
		}


	#endif

	return true;
}



bool sendByteUSB(int &pd, unsigned char data) {

	#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)

    // IMPLEMENTACION PARA LINUX Y MAC

		// Escribimos en el puerto
		int aux= write(pd, &data, 1);

		tcflush(pd, TCIFLUSH); // Forzamos envío del buffer

		// Damos tiempo a procesar las salidas: 100ms por poner algo.
		Dormir(100);
		
		return aux == 1;


	#else

    // IMPLEMENTACION PARA WINDOWS

		int n;

		if(WriteFile(Cport[pd], &data, 1, (LPDWORD)((void *)&n), NULL))
		{
			// Damos tiempo a procesar las salidas: 100ms por poner algo.
			Dormir(100);
		  return (n==1);
		}

	  return false;

	#endif

}



bool receiveByteUSB (int &pd, unsigned char &data) {


	#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)

    // IMPLEMENTACION PARA LINUX Y MAC

		// Esperamos a recibir cadena terminada en '\0'
		bool salir= false;
		while (!salir) {
			int aux= read(pd, &data, 1);
			if (aux > 0)
				salir= true;
		}

	#else 

    // IMPLEMENTACION PARA WINDOWS

		int ndata= 0;
		bool salir= false;
		while (!salir) {

			ReadFile(Cport[pd], (unsigned char *)&data, 1, (LPDWORD)((void *)&ndata), NULL);
			if (ndata == 0)
				Dormir(5);
			else {
				salir= true;
			}
		}


	#endif

	return true;

}

