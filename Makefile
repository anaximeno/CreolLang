FILE=src/creol.cpp
LLVM_CONFIG=llvm-config
LLVM_LIBS=`$(LLVM_CONFIG) --libs core --ldflags --cppflags --system-libs`
ARGS=-g -c -Wall
FLAGS=$(LLVM_LIBS) -std=c++17 $(ARGS)

build:
	@echo Compiling...
	clang++ $(FLAGS) $(FILE)
	@echo Done.

clean:
	rm -f *.o