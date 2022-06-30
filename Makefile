FILE=src/creol.cpp
LLVM_CONFIG=llvm-config
LLVM_LIBS=`$(LLVM_CONFIG) --libs core --ldflags --cppflags --system-libs`
ARGS=-g -Wall
FLAGS=$(LLVM_LIBS) -std=c++17 $(ARGS)
OBJS=creol.o

build:
	@echo Compiling...
	clang++ $(FLAGS) $(FILE) -c
	@echo Done.

test:
	clang++ $(FLAGS) $(OBJS) tests/test.cpp -o test

clean:
	rm -f *.o