# Creoline Language Specification

Language specifications for the Creoline programming language.

## Sections

### Program

```
Program ::= /* empty */
         |  Statements
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

### Block Statement
```

Block ::= '{' Statements '}'
       |  '{' Statements ReturnStatement '}'

```

### General Statements

```
Statements ::= Statements Statement
            |  Statement

Statement ::= SingleLineStatement ';'
           |  FunctionDeclaration
           |  DiLoop
           |  InkuatuLoop
           |  SiStatement

SingleLineStatement ::= VariableDeclaration
                     |  VariableAssignment
                     |  Expression

```

### Loop Statements

```
DiLoop ::= "di" SingleVariableDeclaration "inkuantu" Expression "pui" VariableAssignment Block

InkuantuLoop ::= "inkuantu" Expression Block
```

### If Statements

```
SiStatement ::=   "si" Expression Block
               |  "si" Expression Block "sinon" Block
               |  "si" Expression Block "sinon" SiStatement
```

### Other

```
EmptyOrVoid ::= /* empty */
             | void

ReturnStatement ::= "divolvi" Expression ';'
                 |  "divolvi" EmptyOrVoid ';'
```

# Main References

* http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
* https://github.com/lsegal/my_toy_compiler
* https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html
* https://github.com/xkbeyer/liquid
* https://kuree.gitbooks.io/the-go-programming-language-report/content/18/text.html
* https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm

# License

The BNF of the Creoline programming language is released under the [MIT License](LICENSE).

# Note

***A modified version of the Backus-Naus Form language was used to describe this language.***
