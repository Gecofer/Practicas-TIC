
# Puerto de comunicaciones donde se encuentra Arduino.
COMMPORT = /dev/cu.usbmodem1411

COMMPORTEMISOR = /dev/cu.usbmodem1461

COMMPORTRECEPTOR = /dev/cu.usbmodem1441

# ----- #

arduecho: arduechocpp uartcpp
	@echo Generando binario Arduino...
	avr-gcc -mmcu=atmega328p obj/arduecho.o obj/uart.o -o obj/arduecho.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/arduecho.bin hex/arduecho.hex
	@echo Arduecho compilado. Ejecute make send para enviarlo a la plataforma Arduino.

arduechocpp:
	@echo Compilando arduecho...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/arduecho.o src/arduecho.cpp -Iinclude

uartcpp:
	@echo Compilando biblioteca UART...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/uart.o src/uart.cpp -Iinclude

send:
	@echo Enviando arduecho a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/arduecho.hex

pcecho: pcechocpp ticcommpccpp
	@echo Generando fichero binario pcecho...
	g++ -o bin/pcecho obj/pcecho.o obj/ticcommpc.o

pcechocpp:
	@echo Compilando PCECHO...
	g++ -c -o obj/pcecho.o src/pcecho.cpp -Iinclude

ticcommpccpp:
	@echo Compilando fuentes de biblioteca TICCommPC...
	g++ -c -o obj/ticcommpc.o src/ticcommpc.cpp -Iinclude

# ----- #

arduLEDcontrol: arduLEDcontrolcpp uartcpp
	@echo Generando binario Arduino...
	avr-gcc -mmcu=atmega328p obj/arduLEDcontrol.o obj/uart.o -o obj/arduLEDcontrol.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/arduLEDcontrol.bin hex/arduLEDcontrol.hex
	@echo Arduecho compilado. Ejecute make send para enviarlo a la plataforma Arduino.

arduLEDcontrolcpp:
	@echo Compilando arduLEDcontrol...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/arduLEDcontrol.o src/arduLEDcontrol.cpp -Iinclude

pcLEDcontrol: pcLEDcontrolcpp ticcommpccpp
	@echo Generando fichero binario pcLEDcontrol...
	g++ -o bin/pcLEDcontrol obj/pcLEDcontrol.o obj/ticcommpc.o

pcLEDcontrolcpp:
	@echo Compilando PCECHO...
	g++ -c -o obj/pcLEDcontrol.o src/pcLEDcontrol.cpp -Iinclude

sendLEDcontrol:
	@echo Enviando arduLEDcontrol a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/arduLEDcontrol.hex

# ----- #

arduLEDcontrol10: arduLEDcontrolcpp10 uartcpp
	@echo Generando binario Arduino...
	avr-gcc -mmcu=atmega328p obj/arduLEDcontrol10.o obj/uart.o -o obj/arduLEDcontrol10.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/arduLEDcontrol10.bin hex/arduLEDcontrol10.hex
	@echo Arduecho compilado. Ejecute make send para enviarlo a la plataforma Arduino.

arduLEDcontrolcpp10:
	@echo Compilando arduLEDcontrol...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/arduLEDcontrol10.o src/arduLEDcontrol10.cpp -Iinclude

pcLEDcontrol10: pcLEDcontrolcpp10 ticcommpccpp
	@echo Generando fichero binario pcLEDcontrol10...
	g++ -o bin/pcLEDcontrol10 obj/pcLEDcontrol10.o obj/ticcommpc.o

pcLEDcontrolcpp10:
	@echo Compilando PCECHO...
	g++ -c -o obj/pcLEDcontrol10.o src/pcLEDcontrol10.cpp -Iinclude

sendLEDcontrol10:
	@echo Enviando arduLEDcontrol10 a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/arduLEDcontrol.hex



# ----- #

fotorreceptor:
	@echo Generando binario Arduino...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/fotorreceptor.o src/fotorreceptor.cpp
	avr-gcc -mmcu=atmega328p obj/fotorreceptor.o -o obj/fotorreceptor.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/fotorreceptor.bin hex/fotorreceptor.hex
	@echo fotorreceptor compilado. Ejecute make send para enviarlo a la plataforma Arduino.

sendfotorreceptor:
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/fotorreceptor.hex


emisorArdu: ticcommarducpp emisorArducpp uartcpp arducodifcpp
	@echo Generando binario Arduino emisor...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/uart.o obj/emisorArdu.o -o obj/emisorArdu.bin
	@echo Generando HEX Arduino emisor...
	avr-objcopy -O ihex -R .eeprom obj/emisorArdu.bin hex/emisorArdu.hex
	@echo emisorArdu compilado. Ejecute make sendEmisor para enviarlo a la platforma Arduino.
	
emisorArducpp:
	@echo Compilando emisorArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/emisorArdu.o src/emisorArdu.cpp -Iinclude
sendEmisor:
	@echo Enviando emisorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORTEMISOR) -b 115200 -U flash:w:hex/emisorArdu.hex

ticcommarducpp:
	@echo Compilando ticcommArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/ticcommardu.o src/ticcommardu.cpp -Iinclude

receptorArdu: ticcommarducpp uartcpp receptorArducpp
	@echo Generando binario Arduino receptor...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/uart.o obj/receptorArdu.o -o obj/receptorArdu.bin
	@echo Generando HEX Arduino receptor...
	avr-objcopy -O ihex -R .eeprom obj/receptorArdu.bin hex/receptorArdu.hex
	@echo receptorArdu compilado. Ejecute make sendReceptor para enviarlo a la plataforma Arduino.

receptorArducpp:
	@echo Compilando TICCOmmArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/receptorArdu.o src/receptorArdu.cpp -Iinclude

sendReceptor:
	@echo Enviando receptorArdu...
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORTEMISOR) -b 115200 -U flash:w:hex/receptorArdu.hex

receptorPC: receptorPCcpp ticcommpccpp
	@echo Generando fichero binario receptorPC
	g++ -o bin/receptorPC obj/receptorPC.o obj/ticcommpc.o

receptorPCcpp:
	@echo Compilando receptorPC..
	g++ -c -o obj/receptorPC.o src/receptorPC.cpp -Iinclude

emisorPC: emisorPCcpp ticcommpccpp
	@echo Generando fichero binario emisorPC
	g++ -o bin/emisorPC obj/emisorPC.o obj/ticcommpc.o

emisorPCcpp:
	@echo Compilando emisorPC..
	g++ -c -o obj/emisorPC.o src/emisorPC.cpp -Iinclude


arducodifcpp:
	@echo Compilando fuentes de biblioteca arducodif...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/arducodif.o src/arducodif.cpp -Iinclude

# ----- #


fotoArdu: ticcommarducpp uartcpp fotoArducpp
	@echo Generado binario Arduino...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/uart.o obj/fotoArdu.o -o bin/fotoArdu.bin
	@echo Generando HEX Arduino receptor...
	avr-objcopy -O ihex -R .eeprom bin/fotoArdu.bin hex/fotoArdu.hex
	@echo fotoArdu compilado. Ejecute make sendReceptorFoto para enviarlo a la plataforma Arduino.

fotoArducpp:
	@echo Compilando fotoArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/fotoArdu.o src/fotoArdu.cpp -Iinclude

fotoPC: fotoPCcpp ticcommpccpp
	@echo Generando fichero binario fotoPC...
	g++ -o bin/fotoPC obj/fotoPC.o obj/ticcommpc.o

fotoPCcpp:
	@echo Compilando fotoPC...
	g++ -c -o obj/fotoPC.o src/fotoPC.cpp -Iinclude


sendReceptorFoto:
	@echo Eviando fotoArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:$(HEX)/fotoArdu.hex


# ----- #

emisorArduS5: ticcommarducpp emisorArduS5cpp uartcpp arducodifcpp
	@echo Generando binario Arduino emisor...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/uart.o obj/emisorArduS5.o obj/arducodif.o -o obj/emisorArduS5.bin
	@echo Generando HEX Arduino emisor...
	avr-objcopy -O ihex -R .eeprom obj/emisorArduS5.bin hex/emisorArduS5.hex
	@echo emisorArduS5 compilado. Ejecute make sendEmisor para enviarlo a la platforma Arduino.
	
emisorArduS5cpp:
	@echo Compilando emisorArduS5...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/emisorArduS5.o src/emisorArduS5.cpp -Iinclude

sendEmisorS5:
	@echo Enviando emisorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORTEMISOR) -b 115200 -U flash:w:hex/emisorArduS5.hex

receptorArduS5: ticcommarducpp uartcpp receptorArducppS5 arducodifcpp
	@echo Generando binario Arduino receptor sesion 5...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/uart.o obj/receptorArduS5.o obj/arducodif.o -o obj/receptorArduS5.bin
	@echo Generando HEX Arduino receptor sesion 5...
	avr-objcopy -O ihex -R .eeprom obj/receptorArduS5.bin hex/receptorArduS5.hex
	@echo receptorArdu compilado. Ejecute make sendReceptorS5 para enviarlo a la plataforma Arduino.

receptorArducppS5:
	@echo Compilando TICCOmmArdu sesion 5...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/receptorArduS5.o src/receptorArduS5.cpp -Iinclude

sendReceptorS5:
	@echo Enviando receptorArdu sesion 5...
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORTRECEPTOR) -b 115200 -U flash:w:hex/receptorArduS5.hex

receptorPCS5: receptorPCcppS5 ticcommpccpp
	@echo Generando fichero binario receptorPCS5
	g++ -o bin/receptorPCS5 obj/receptorPCS5.o obj/ticcommpc.o
receptorPCcppS5:
	@echo Compilando receptorPC sesion 5..
	g++ -c -o obj/receptorPCS5.o src/receptorPCS5.cpp -Iinclude

emisorPCS5: emisorPCcppS5 ticcommpccpp
	@echo Generando fichero binario emisorPCS5
	g++ -o bin/emisorPCS5 obj/emisorPCS5.o obj/ticcommpc.o 

emisorPCcppS5:
	@echo Compilando emisorPC sesion 5..
	g++ -c -o obj/emisorPCS5.o src/emisorPCS5.cpp -Iinclude

# ----- #


clean:
	@echo
	@echo Haciendo limpieza...
	rm -Rf $(OBJ)/* $(BIN)/* $(HEX)/*
	@echo Limpieza terminada
	@echo