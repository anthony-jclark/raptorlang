
http://www.programcreek.com/2011/02/how-compiler-works/
- ~~lexical analysis~~ --> tokens
- syntax analysis --> AST
- semantic analysis --> Symbol table
- IR generation
- IR optimization --> IR
- code generation
- optimization --> native code

## TODO

+ use visitor pattern in AST (double dispatch)
+ setup continuous integration testing
+ user literals (_s, _h, _mi, _km, etc.)
+ use GSL
    * owner<T*> use in libraries/containers (not general code)
- multiple return
- functional mode (pure mode)
    + no mutability
    + no I/O
    + not procs just funcs
- list of operators (pythong script)
- do all constexprs at compile time
- treat variables and unary operators as atoms
- change language grammar (more C/C++ like)
- different number bases (hex, binary, oct)
- cmake release vs debug
- set/let
- cleanup included headers
- parallel compilation
- error messages print the line
- visitor pattern for codegen
- cmake find library
- define loops in terms of each other
- error messages at the file level (consider the compiled file not the library code)
- always delete, but allow move operations (not really shared)
- warn for expressions with no effect
- anon functions

## Purpose

Learn how to create a programming language with a focus on parallel computation.

- link to CPPCON talk
- learn C++ *process* (I'm good at coding)
- simple structure
    + including namespacing



