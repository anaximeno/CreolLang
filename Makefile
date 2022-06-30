.DEFAULT_GOAL := creol

.PHONY: creol main.o creol.o parser.o scanner.o parser.cc parser.hh scanner.cc

CPP_VERSION = -std=c++17

creol: main.o creol.o parser.o scanner.o
	g++ $(CPP_VERSION) creol.o parser.o scanner.o main.o -g -o creol

main.o: main.cpp parser.o scanner.o creol.o
	g++ $(CPP_VERSION) main.cpp parser.o scanner.o creol.o -c -g -c

creol.o:
	g++ $(CPP_VERSION) src/creol.cc -g -c

parser.o: parser.cc parser.hh scanner.cc creol.o
	g++ $(CPP_VERSION) parser.cc scanner.cc creol.o -g -c

scanner.o: scanner.cc parser.cc creol.o
	g++ $(CPP_VERSION) scanner.cc parser.cc creol.o -g -c

parser.cc parser.hh:
	bison -dt rules/parser.y -o parser.cc

scanner.cc:
	flex -o scanner.cc rules/scanner.l

clean:
	rm *.o parser.cc parser.hh scanner.cc parser.output creoline
