#!/bin/bash

COMPILER=g++
OUTFILE=parser

# Compile the scanner
flex -o scanner.cc scanner.l

if [[ $? -eq 0 ]]
then
    # Compile the parser
    bison -dt parser.y -o parser.cc

    if [[ $? -eq 0 ]]
    then
        $COMPILER -g -o $OUTFILE parser.cc scanner.cc ../creol.o
        if [[ $? -eq 0 ]]
        then
            echo -e "\nParser sucessfully compiled!\n"
        else
            echo -e "\nError: could not compile the parser!"
        fi

        # Remove the generated parser
        rm parser.cc parser.hh
    else
        echo -e "\nError: could not create the parser!"
    fi

    # Remove the generated parser
    rm scanner.cc
else
    echo -e "\nError: could not create the scanner!"
fi
