# CreolLang

**CreolLang** or **Creol** is a programming language based on the **Cape Verdian Creole**. It was made to be easy for anyone who understands Cape Verdean Creole while keeping the same versatility as some other languages, such as C, Go, and Rust.

## Description

The syntax of this programming language was initially based on C, Go and Rust, but other programming languages such as Liquid played a good role in the initial design.

For more concrete specifications about the language, you are recommended to read the [CreolLang Language Specification](./docs/creol-lang-spec.md).

### More:

The file extension of the CreolLang programming language is **.crl** and the compiler's name is **creol**.

## Installation

It isn't installable on any OS yet, but it still can be tested using an Unix based operating system. It basically depends on **clang++** or **g++** to compile the source code, and **bison** and **flex** to compile the language rules.

If you are on a Debian (or Ubuntu) based linux operating system you can install the dependencies using the following command:

```
apt install make flex bison g++ clang
```

And then compile the compiler using:

```
make
```

For a release build use:

```
make release
```

The result of the compilation will be an executable named **creol** which you can execute using:

```
./creol
```

## Usage

The first thing to do after compiling the compiler is to execute the help command:

```
./creol --help
```

After executing that command you may see the usage section and some of its options.

An example of how it could be used is to compile one of the examples files on the examples folder:

```
./creol examples/example03.crl
```

You may see the code on example03.crl converted to the C language code on the terminal.

For building the code you could use the **-b** or **--build** flag:

```
./creol examples/example03.crl -b
```
Then execute the compiled code with:

```
./a.out
```

The CreolLang compiler currently has only a few usage options and may be extended to additional tooling and improvements on future releases.
<!--
## Visuals

TODO...

## Contributing

TODO...

-->

## License

All the code and specifications of the CreolLang programming language are currently under the [MIT License](./LICENSE).

## Project status

Under development.
