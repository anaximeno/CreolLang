# .DEFAULT_GOAL := creol

.PHONY: creol

CC = clang++

FLAGS = -std=c++17 -fPIC

DBG_FLAGS = $(FLAGS) -g

RLS_FLAGS = $(FLAGS) -O3 -finline-functions

OBJS = main.o ast.o cli.o parser.o scanner.o

SRCS = main.cpp \
	   src/creol/ast.cc \
	   src/creol/cli.cc \
	   parser.cc scanner.cc \
	   include/external/argparse.hpp

creol: dbg-obj
	$(CC) -o $@ $(DBG_FLAGS) $(OBJS)

dbg-obj: $(SRCS)
	@echo "~~ Debug build ~~"
	$(CC) -c $(DBG_FLAGS) $^

debug: creol

parser.cc parser.hh:
	bison -dt rules/parser.y -o parser.cc

scanner.cc:
	flex -o scanner.cc rules/scanner.l

clean:
	rm *.o parser.cc parser.hh scanner.cc parser.output creol

rls-obj: $(SRCS)
	@echo "~~ Release build ~~"
	$(CC) -c $(RLS_FLAGS) $^

release: rls-obj
	$(CC) -o creol $(RLS_FLAGS) -O3 -finline-functions $(OBJS)
