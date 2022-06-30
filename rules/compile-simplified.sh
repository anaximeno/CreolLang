#!/bin/bash

COMPILER=clang++
OUTFILE=parser-simplified
COMPIL_ARGS="../creol.o -std=c++17 `llvm-config --libs core --ldflags --cppflags --system-libs`"
# Compile the scanner-simplified
flex -o scanner-simplified.cc scanner-simplified.l

if [[ $? -eq 0 ]]
then
    # Compile the parser-simplified
    bison -dt parser-simplified.y -o parser-simplified.cc

    if [[ $? -eq 0 ]]
    then
        $COMPILER -g -o $OUTFILE parser-simplified.cc scanner-simplified.cc $COMPIL_ARGS
        if [[ $? -eq 0 ]]
        then
            echo -e "\nParser-simplified sucessfully compiled!\n"
        else
            echo -e "\nError: could not compile the parser-simplified!"
        fi

        # Remove the generated parser-simplified
        rm parser-simplified.cc parser-simplified.hh
    else
        echo -e "\nError: could not create the parser-simplified!"
    fi

    # Remove the generated parser-simplified
    rm scanner-simplified.cc
else
    echo -e "\nError: could not create the scanner-simplified!"
fi
