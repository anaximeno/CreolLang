# .DEFAULT_GOAL := creol

.PHONY: creol

CC = g++

FLAGS = -std=c++17 -g -O -fPIC -Wall

OBJS = main.o ast.o cli.o parser.o scanner.o

SRCS = main.cpp \
	   src/creol/ast.cc \
	   src/creol/cli.cc \
	   parser.cc scanner.cc

creol: $(OBJS)
	$(CC) -o $@ $(FLAGS) $^

$(OBJS): $(SRCS)
	$(CC) -c $(FLAGS) $^

parser.cc parser.hh:
	bison -dt rules/parser.y -o parser.cc

scanner.cc:
	flex -o scanner.cc rules/scanner.l

clean:
	rm *.o parser.cc parser.hh scanner.cc parser.output creol
