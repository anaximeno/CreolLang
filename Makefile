.DEFAULT_GOAL := creoline

.PHONY: creoline creol.o parser.o scanner.o parser.cc parser.hh scanner.cc

OBJS=creol.o

creoline: creol.o parser.o scanner.o
	g++ creol.o parser.o scanner.o -g -o creoline

creol.o:
	g++ src/creol.cc -g -c

parser.o: parser.cc parser.hh scanner.cc creol.o
	g++ parser.cc scanner.cc creol.o -g -c

scanner.o: scanner.cc parser.cc creol.o
	g++ scanner.cc parser.cc creol.o -g -c

parser.cc parser.hh:
	bison -dt rules/parser.y -o parser.cc

scanner.cc:
	flex -o scanner.cc rules/scanner.l

clean:
	rm *.o parser.cc parser.hh scanner.cc parser.output creoline
