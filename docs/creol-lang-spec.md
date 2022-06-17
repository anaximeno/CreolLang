***(!!! TO BE UPDATED...)***
# CreolLang Language Specification

Language specifications for the CreolLang programming language.

## Sections

### Program

```
Program ::= Statements
```

### Variable Declaration

```
VariableDeclaration ::= SingleVariableDeclaration
                     |  MultipleVariablesDeclaration

SingleVariableDeclaration ::= Type Identifier
                           |  Type VariableAssignment

MultipleVariablesDeclaration ::= Type VariablesList

VariablesList ::= VariablesList ',' Identifier
               |  VariablesList ',' VariableAssignment
               |  VariableAssignment
               |  Identifier

VariableAssignment ::= Identifier '=' Expression
```

### Expressions

```
Expression ::= Expression AritmeticOperator Expression
            |  Expression ComparativeOperator Expression
            |  Expression BooleanOperator Expression
            |  FunctionCall
            |  Identifier
            |  Literal
```

### Basic Binary Operations
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

### Function Staments

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

### General Statements

```
Statements ::= Statements Statement
            |  Statement

Statement ::= SingleLineStatement
           |  FunctionDeclaration
           |  InkuatuLoop
           |  SiStatement
           |  DiLoop

SingleLineStatement ::= VariableDeclaration ';'
                     |  VariableAssignment ';'
                     |  Expression ';'
                     |  ReturnStatement ';'
                     | /* empty */
                     | ';'

ReturnStatement ::= "divolvi" Expression
                 |  "divolvi" EmptyOrVoid

Block ::= '{' Statements '}'
```

### Loop Statements

```
DiLoop ::= "di" DiLoopStart "inkuantu" Expression "pui" VariableAssignment Block

DiLoopStart ::= SingleVariableDeclaration
             |  VariableAssignment

InkuantuLoop ::= "inkuantu" Expression Block
```

### If Statements

```
SiStatement ::= "si" Expression Block
             |  "si" Expression Block "sinon" Block
             |  "si" Expression Block "sinon" SiStatement
```

### Other

```
EmptyOrVoid ::= /* empty */
             |  void
```

# License

The specification of the CreolLang programming language is released under the [MIT License](LICENSE).

# Note

***A modified version of the Backus-Naus Form language was used for describing this language.***
