# Creoline BNF Spec

Language specifications for the Creoline programming language.

It was based on the some programming languages like **C**, **Go**, **Rust**, and also, the **Cape Verdian Creole**.

## Variable Declaration

```html
<VarDecl> ::= <Type> <Declarations>

<Declarations> ::= <Declarations> ',' <Declaration>
                | <Declaration>

<Declaration> ::= <Identifier>
               | <Identifier> '=' <Expression>
```

## Expressions

```html
<Expression> ::= <Expression> <AritmeticOperation> <Expression>
              |  <Expression> <ComparativeOperation> <Expression>
              |  <Expression> <BooleanOperation> <Expression>
              |  <Identifier>
              |  <Number>
              |  <Identifier> '(' <FunctionArguments> ')'
              |  <Identifier> '(' ')'
```

## Basic Binary Operations
```html
<AritmeticOperation> ::= '+' | '-' | '*' | '/'

<ComparativeOperation> ::= '<' | '<=' | '>' | '>=' | '==' | '!='

<BooleanOperation> ::= '&&' | '||' 
```

## Function Staments

```html
<FunctionArguments> ::= <FunctionArguments> ',' <Expression>
                     |  <Expression>

<FunctionDeclaration> ::= <Type> <Identifier> '('<FunctionParameters>')' <Block>
                       |  <Type> <Identifier> '(' <NoFunctionParameters> ')' <Block>

<NoFunctionParamaters> ::=  | void

<FunctionParameters> ::= <FunctionParameters> ',' <Type> <Identifier>
                      |  <Type> <Identifier> 
```

## Block Statement
```html

<Block> ::= '{' <Statements> '}' | '{' <Statements> <ReturnStatement> '}'

```

## Return Statement

```html

<ReturnStatement> ::= "divolvi" <Expression> ';'
                   | "divolvi" <NoReturnValue> ';'

<NoReturnValue> ::= | void

```

## General Statements

```html
<Statements> ::= <Statements> <Statement>
              | <Statement>

<Statement> ::= <SingleLineStatement> ';'
             |  <FunctionDeclaration>
             |  <DiTiLoop>
             |  <InkuatuLoop>
             |  <SiStatement>

<SingleLineStatement> ::= <VariableDeclaration>
                       |  <Declaration>
                       |  <Expression>

```

## Loop Statements

```html
<DiTiLoop> ::= "di" <DiTiLoopInitStatement> "ti" <Expression> "pui" <Declaration> <Block>

<InkuantuLoop> ::= "inkuantu" <Expression> <Block>
```

## If Statements

```html
<SiStatement> ::= "si" <Expression> <Block>
               |  "si" <Expression> <Block> "sinon" <Block>
               |  "si" <Expression> <Block> "sinon" <SiStatement>
```

### References

* http://gnuu.org/2009/09/18/writing-your-own-toy-compiler/
* https://github.com/lsegal/my_toy_compiler
* https://llvm.org

## License

The BNF of the Creoline programming language is released under the [MIT License](LICENSE).