.DEFAULT_GOAL := build

.PHONY: compile-libs generate-parser generate-scanner build

OBJS=creol.o

compile-libs:
	g++ src/creol.cc -g -Wall -c

generate-parser: compile-libs
	bison -dt rules/parser.y -o parser.cc

generate-scanner: generate-parser
	flex -o scanner.cc rules/scanner.l

build: generate-parser generate-scanner
	g++ parser.cc scanner.cc $(OBJS) -o creoline

clean:
	rm *.o parser.cc parser.hh scanner.cc
	rm parser.output creoline