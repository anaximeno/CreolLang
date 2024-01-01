.DEFAULT_GOAL := creol

.PHONY: creol debug release clean

CC = clang++

OUTPUT = creol

FLAGS = -std=c++17 -fPIC

DBG_FLAGS = $(FLAGS) -g -Wall

RLS_FLAGS = $(FLAGS) -O3 -finline-functions

OBJS = main.o ast.o cli.o parser.o scanner.o

SRCS = main.cpp \
	   src/creol/ast.cc \
	   src/creol/cli.cc \
	   parser.cc scanner.cc \
	   include/external/argparse.hpp

# The default build is debug.
# Change to release if wanted.
creol: debug
	@echo "\n\nRun the compiler with:"
	@echo "\n  ./creol --help\n"

dbg-obj: $(SRCS)
	@echo "~~ Debug build ~~"
	$(CC) -c $(DBG_FLAGS) $^

debug: dbg-obj
	$(CC) -o $(OUTPUT) $(DBG_FLAGS) $(OBJS)

rls-obj: $(SRCS)
	@echo "~~ Release build ~~"
	$(CC) -c $(RLS_FLAGS) $^

release: rls-obj
	$(CC) -o $(OUTPUT) $(RLS_FLAGS) $(OBJS)

parser.cc parser.hh:
	bison -dt rules/parser.y -o parser.cc

scanner.cc:
	flex -o scanner.cc rules/scanner.l

clean:
	rm *.o creol
