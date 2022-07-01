# .DEFAULT_GOAL := creol

.PHONY: creol main.o creol.o parser.o scanner.o parser.cc parser.hh scanner.cc

CPP_VERSION = -std=c++17

creol: main.o creol.o parser.o scanner.o
	g++ $(CPP_VERSION) creol.o parser.o scanner.o main.o -g -o creol

main.o: main.cpp parser.cc scanner.cc src/creol.cc include/external/argparse.hpp
	g++ $(CPP_VERSION) main.cpp parser.cc scanner.cc src/creol.cc include/external/argparse.hpp -c -g -c

creol.o:
	g++ $(CPP_VERSION) src/creol.cc -g -c

parser.o: parser.cc parser.hh scanner.cc src/creol.cc
	g++ $(CPP_VERSION) parser.cc scanner.cc src/creol.cc -g -c

scanner.o: scanner.cc parser.cc src/creol.cc
	g++ $(CPP_VERSION) scanner.cc parser.cc src/creol.cc -g -c

parser.cc parser.hh:
	bison -dt rules/parser.y -o parser.cc

scanner.cc:
	flex -o scanner.cc rules/scanner.l

clean:
	rm *.o parser.cc parser.hh scanner.cc parser.output creol
