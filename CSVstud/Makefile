all: build clean

build: main.o CSVParser.o TablePrinter.o CSVTableFasade.o StudentProcessor.o
	g++ main.o CSVParser.o TablePrinter.o CSVTableFasade.o StudentProcessor.o -o csvstud

main.o: main.cpp
	g++ -c main.cpp

CSVParser.o: 
	g++ -c "../CSVcat/CSVParser/CSVParser.cpp"

TablePrinter.o: 
	g++ -c "../CSVcat/TablePrinter/TablePrinter.cpp"

CSVTableFasade.o:
	g++ -c "../CSVcat/CSVTableFasade/CSVTableFasade.cpp"

StudentProcessor.o:
	g++ -c StudentProcessor/StudentProcessor.cpp

clean:
	find . -name "*.o" -type f -delete$ 