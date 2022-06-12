# Creoline BNF Spec

Language specifications for the Creoline programming language.

## Program

```
Program ::= /* empty */
         |  Statements
```

## Variable Declaration

```
VariableDeclaration ::= SingleVariableDeclaration
                     |  MultipleVariablesDeclaration

SingleVariableDeclaration ::= Type Identifier
                           |  Type VariableAssignment

MultipleVariablesDeclaration ::= Type VariablesList

VariablesList ::= VariablesList ',' Identifier
               |  VariablesList ',' VariableAssignment

VariableAssignment ::= Identifier '=' Expression
```

## Expressions

```DiTiLoopInitStatement ::= Type Identifier '=' Expression
                        | Identifier '=' Expression

Expression ::= Expression AritmeticOperator Expression
            |  Expression ComparativeOperator Expression
            |  Expression BooleanOperator Expression
            |  FunctionCall
            |  Identifier
            |  Literal
```

## Basic Binary Operations
```
AritmeticOperator ::= '+'
                   |  '-'
                   |  '*'
                   |  '/'

ComparativeOperator ::= '<'
                     |  '<='
                     |  '>'
                     |  '>='
                     |  '==' 
                     |  '!='

BooleanOperator ::= '&&'
                 |  '||' 
```

## Function Staments

```
FunctionArguments ::= FunctionArguments ',' Expression
                   |  Expression

FunctionDeclaration ::= Type Identifier '('FunctionParameters')' Block
                     |  Type Identifier '(' EmptyOrVoid ')' Block

FunctionParameters ::= FunctionParameters ',' Type Identifier
                    |  Type Identifier

FunctionCall ::= Identifier '(' FunctionArguments ')'
              |  Identifier '(' ')'
```

## Block Statement
```

Block ::= '{' Statements '}'
       |  '{' Statements ReturnStatement '}'

```

## General Statements

```
Statements ::= Statements Statement
            |  Statement

Statement ::= SingleLineStatement ';'
           |  FunctionDeclaration
           |  DiLoop
           |  InkuatuLoop
           |  SiStatement

SingleLineStatement ::= VariableDeclaration
                     |  Declaration
                     |  Expression

```

## Loop Statements

```
DiLoop ::= "di" SingleVariableDeclaration "inkuantu" Expression "pui" VariableAssignment Block

InkuantuLoop ::= "inkuantu" Expression Block
```

## If Statements

```
SiStatement ::=   "si" Expression Block
               |  "si" Expression Block "sinon" Block
               |  "si" Expression Block "sinon" SiStatement
```

## Other

```
EmptyOrVoid ::= /* empty */
             | void

ReturnStatement ::= "divolvi" Expression ';'
                 |  "divolvi" EmptyOrVoid ';'
```

# References

* http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
* https://github.com/lsegal/my_toy_compiler
* https://llvm.org

# License

The BNF of the Creoline programming language is released under the [MIT License](LICENSE).

# Note

***It was used a modified version of the Backus-Naus Form language to describe this language.***
