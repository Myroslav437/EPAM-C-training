all: build clean

build: main.o CSVParser.o TablePrinter.o CSVTableFasade.o 
	g++ main.o CSVParser.o TablePrinter.o CSVTableFasade.o -o csvcat

main.o: main.cpp
	g++ -c main.cpp

CSVParser.o: 
	g++ -c CSVParser/CSVParser.cpp

TablePrinter.o: 
	g++ -c TablePrinter/TablePrinter.cpp

CSVTableFasade.o:
	g++ -c CSVTableFasade/CSVTableFasade.cpp

clean:
	find . -name "*.o" -type f -delete