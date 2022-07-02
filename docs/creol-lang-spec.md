# CreolLang Language Specification

Language specifications for the CreolLang programming language.

## General Statements

```html
<program> ::= <statements>

<statements> ::= <statements> <statement>
               | <statement>

<statement> ::= <expression_statement>
              | <compound_statement>
              | <selection_statement>
              | <iteration_statement>
              | <jump_statement>
              | <function_declaration>
              | <declaration>
              | <import_statement>
```

## Import Statements

```html

<import_statement> ::= T_IMPRISTAN <single_import>

<single_import> ::= T_STR_LIT

```
## Variable declaration

```html
<type_specifier> ::= T_TYPE_INT
                   | T_TYPE_FLOAT
                   | T_TYPE_VOID
                   | T_TYPE_BOOL

<constant> ::= T_INT_LIT
             | T_FLOAT_LIT
             | T_BOOL_LIT
             | T_STR_LIT

<identifier> ::= T_IDENT

<declarator> ::= <identifier>

<declaration> ::= <type_specifier> <init_declarator>

<init_declarator> ::= <declarator>
                    | <declarator> <assignment_operator> <initializer>

<initializer> ::= <expression>

```

## Binary Expressions

```html
<logical_or_expressions> ::= <logical_and_expressions>
                           | <logical_or_expressions> T_OR <logical_and_expressions>

<logical_and_expressions> ::= <equality_expression>
                            | <logical_and_expressions> T_AND <equality_expression>

<equality_expression> ::= <relational_expression>
                        | <equality_expression> T_EQ <relational_expression>
                        | <equality_expression> T_NE <relational_expression>

<relational_expression> ::= <additive_expression>
                          | <relational_expression> T_LT <additive_expression>
                          | <relational_expression> TGT <additive_expression>
                          | <relational_expression> T_LE <additive_expression>
                          | <relational_expression> T_GE <additive_expression>

<additive_expression> ::= <multiplicative_expression>
                        | <additive_expression> T_PLUS <multiplicative_expression>
                        | <additive_expression> T_MINUS <multiplicative_expression>

<multiplicative_expression> ::= <unary_expression>
                              | <multiplicative_expression> T_MUL <primary_expression>
                              | <multiplicative_expression> T_DIV <primary_expression>
```

## Other Expressions

```html
<expression> ::= <assignment_expression>
               | <function_call>

<constant_expression> ::= <logical_or_expressions>

<unary_expression> ::= <primary_expression>
                     | T_MINUS <primary_expression> UMINUS

<primary_expression> ::= <identifier>
                       | <constant>
                       | '(' <expression> ')'

<assignment_expression> ::= <constant_expression>
                          | <primary_expression> <assignment_operator> <assignment_expression>
```

## Assingment Operations

```html
<assignment_operator> ::= '='

```

## Function Statements

```html
<function_declaration> ::= <type_specifier> <declarator> '(' <parameter_optional_list> ')' <compound_statement>

<parameter_optional_list> ::= <parameter_list>
                            | λ

<parameter_list> ::= <parameter_declaration>
                   | <parameter_list> ',' <parameter_declaration>

<parameter_declaration> ::= <type_specifier> <declarator>

<argument_list> ::= <argument_list> ',' <expression> | <expression>

<function_call> ::= <identifier> '(' <argument_list> ')'
                  | <identifier> '(' ')'
                  | <mostra_func_call>

<mostra_func_call> ::= T_MOSTRA '(' <argument_list> ')'
                     | T_MOSTRA '(' ')'

<expression_statement> ::= <expression> ';'
                         | ';'

<compound_statement> ::= '{' <statements> '}'
                       | '{' '}'

```

## Selection statement

```html
<selection_statement> ::= T_SI <expression> <compound_statement>
                        | T_SI <expression> <compound_statement> T_SINON <else_then>

<else_then> ::= <compound_statement>
              | <selection_statement>
```

## Iteration statement

```html
<iteration_statement> ::= T_NKUANTU <expression> <compound_statement>
                        | T_DI <expression> ';' <expression> ';' <expression>
```

## Jump statement

```html
<jump_statement> ::= T_PARA ';'
                   | T_CONTINUA ';'
                   | T_DIVOLVI <expression> ';'
                   | T_DIVOLVI ';'
```

# License

The specification of the CreolLang programming language is released under the [MIT License](LICENSE).

# Note

***A modified version of the Backus-Naus Form language was used for describing this language.***

<!--
Contribution from Tamiris Nascimento.
-->