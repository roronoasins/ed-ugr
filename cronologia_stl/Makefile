BIN = bin
OBJ = obj
SRC = src
INCLUDE = include
LIB = lib
CPPFLAGS = -I$(INCLUDE) -std=c++11 -Wall -g

pruebacrono: $(BIN)/pruebacronologia

union: $(BIN)/union_cronologia

intervalo: $(BIN)/intervalo_cronologia

palabra_clave: $(BIN)/palabra_clave

recuento_eventos: $(BIN)/recuento_eventos

$(BIN)/pruebacronologia: $(OBJ)/pruebacronologia.o $(OBJ)/FechaHistorica.o	$(OBJ)/Cronologia.o
	g++ -o $@ $^

$(BIN)/union_cronologia: $(OBJ)/union_cronologia.o $(OBJ)/FechaHistorica.o	$(OBJ)/Cronologia.o
	g++ -o $@ $^

$(BIN)/intervalo_cronologia: $(OBJ)/intervalo_cronologia.o $(OBJ)/FechaHistorica.o	$(OBJ)/Cronologia.o
	g++ -o $@ $^

$(BIN)/palabra_clave: $(OBJ)/palabra_clave.o $(OBJ)/FechaHistorica.o	$(OBJ)/Cronologia.o
	g++ -o $@ $^

$(BIN)/recuento_eventos: $(OBJ)/recuento_eventos.o $(OBJ)/FechaHistorica.o	$(OBJ)/Cronologia.o
	g++ -o $@ $^

$(OBJ)/pruebacronologia.o: $(SRC)/pruebacronologia.cpp $(INCLUDE)/Cronologia.h
	g++ -c $(CPPFLAGS) -o $@ $<

$(OBJ)/union_cronologia.o: $(SRC)/union_cronologia.cpp $(INCLUDE)/Cronologia.h
	g++ -c $(CPPFLAGS) -o $@ $<

$(OBJ)/intervalo_cronologia.o: $(SRC)/intervalo_cronologia.cpp $(INCLUDE)/Cronologia.h
	g++ -c $(CPPFLAGS) -o $@ $<

$(OBJ)/palabra_clave.o: $(SRC)/filtrado_palabra_clave.cpp $(INCLUDE)/Cronologia.h
	g++ -c $(CPPFLAGS) -o $@ $<

$(OBJ)/recuento_eventos.o: $(SRC)/recuento_eventos.cpp $(INCLUDE)/Cronologia.h
	g++ -c $(CPPFLAGS) -o $@ $<

$(OBJ)/Cronologia.o: $(SRC)/Cronologia.cpp $(INCLUDE)/Cronologia.h
	g++ -c $(CPPFLAGS) -o $@ $<

$(OBJ)/FechaHistorica.o: $(SRC)/FechaHistorica.cpp $(INCLUDE)/FechaHistorica.h
	g++ -c $(CPPFLAGS) -o $@ $<

clean:
	@echo Borrando...
	-rm $(OBJ)/*
	@echo Objetos borrados.
	-rm $(BIN)/*
	@echo Ejecutables borrados.

mrproper: clean
	-rm  doc/html/* doc/latex/*

documentacion:
	doxygen doc/doxys/Doxyfile
