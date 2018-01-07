BIN 	= bin
OBJ 	= obj
LIB 	= lib
SRC 	= src
INCLUDE = include

# Nombre que recibirá el fichero ejecutable
TARGETS = $(BIN)/testProbabilidades $(BIN)/testHuffman

# Orden que será ejecutada por defecto
default : $(TARGETS)

# ************ Creacion de Objetos ************	

$(OBJ)/utilsPC.o: $(SRC)/utilsPC.cpp $(INCLUDE)/utilsPC.h
	g++ -c $(SRC)/utilsPC.cpp -o $(OBJ)/utilsPC.o -Iinclude/

$(OBJ)/Huffman.o: $(SRC)/Huffman.cpp $(INCLUDE)/Huffman.h
	g++ -c $(SRC)/Huffman.cpp -o $(OBJ)/Huffman.o -Iinclude/

$(OBJ)/testProbabilidades.o: $(OBJ)/utilsPC.o $(INCLUDE)/utilsPC.h 
	g++ -c $(SRC)/testProbabilidades.cpp -o $(OBJ)/testProbabilidades.o -Iinclude/

$(OBJ)/testHuffman.o: $(OBJ)/utilsPC.o $(INCLUDE)/utilsPC.h $(OBJ)/Huffman.o $(INCLUDE)/Huffman.h 
	g++ -c $(SRC)/testHuffman.cpp -o $(OBJ)/testHuffman.o -Iinclude/


$(BIN)/testProbabilidades: $(OBJ)/testProbabilidades.o $(OBJ)/utilsPC.o 
	g++ -o $(BIN)/testProbabilidades $(OBJ)/testProbabilidades.o $(OBJ)/utilsPC.o 

$(BIN)/testHuffman: $(OBJ)/testHuffman.o $(OBJ)/utilsPC.o $(OBJ)/Huffman.o 
	g++ -o $(BIN)/testHuffman $(OBJ)/testHuffman.o $(OBJ)/utilsPC.o $(OBJ)/Huffman.o 


# ************ Limpieza ************

clean:
	echo "Limpiando..."
	rm -rf $(OBJ)/*

mrproper: clean
	rm -rf $(BIN)/*