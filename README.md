## TODO

- General
    + namespacing
    + setup continuous integration testing
    + user literals (_s, _h, _mi, _km, etc.)
    + automate tokens filename (rex.h.in.cmake, etc.)
- rex
    + nested comments (Lua?)
    + tokens to consider (clang -cc1 -dump-tokens temp.cpp)
        * https://msdn.microsoft.com/en-us/library/3bstk3k5.aspx
        * comma
        * built-in types (deduced?)
        * name for each operator (star, equal, )
        * brace, bracket, angle bracket, etc.
        * literals (string, numeric, etc.)
        * c++ seems to have a token for every keyword (and IDs, etc.)
        * keywords, identifiers, literals (integer, float, boolean, char, string[char*], pointer), operators, punctuators
        * https://msdn.microsoft.com/en-us/library/126fe14k.aspx (operators)
    + ... range or ..
    + Operators are used in expressions to describe operations involving one or more operands. For example, the expression a + b uses the + operator to add the two operands a and b. Punctuators are for grouping and separating.
    + Operator or punctuator    Alternative representation
&&  and
|   bitor
||  or
^   xor
~   compl
&   bitand
&=  and_eq
|=  or_eq
^=  xor_eq
!   not
!=  not_eq

https://github.com/jarro2783/cxxopts
https://code.google.com/p/cpp-project-template/wiki/Basics
- not using logging
- not using preferences
- not using GUI
- not using interactive
- not using UnitTest++
- not using {AUTHORS, COPYING, ChangeLog, INSTALL, configure, include, share, thirdparty}


# Dev Commands




# raptorlang

- define loops in terms of each other
- error messages at the file level (consider the compiled file not the library code)
- always delete, but allow move operations (not really shared)

## Purpose

Learn how to create a programming language with a focus on parallel computation.

- link to CPPCON talk
- learn C++ *process* (I'm good at coding)
- simple structure
    + including namespacing

## REX (lexer)

## RAR (parser)

## Directory Tree

- going by what makes the most sense
- relative header files
- submodules
    + http://stackoverflow.com/questions/5828324/update-git-submodule-to-latest-commit-on-origin

```text
├── bin     : 
├── build   : 
├── doc     :
├── lib     : 
├── src     : source for the application
└── test    : source for tests
```

## Building the compiler

CMake build system




## Profiling

bin/raptorlang -v 10 --vmodule main=3
ish: 'bin/raptorlang -v 10 --vmodule…' terminated by signal SIGBUS (Misaligned address error)

SET (CMAKE_BUILD_TYPE debug)


==57114== Memcheck, a memory error detector
==57114== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==57114== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==57114== Command: bin/raptorlang
==57114==
==57114== Invalid write of size 1
==57114==    at 0x100006CC7: main (main.cpp:167)
==57114==  Address 0x10098e85f is 0 bytes after a block of size 15 alloc'd
==57114==    at 0x100174EBB: malloc (in /usr/local/Cellar/valgrind/3.11.0/lib/valgrind/vgpreload_memcheck-amd64-darwin.so)
==57114==    by 0x1001B943D: operator new(unsigned long) (in /usr/lib/libc++.1.dylib)
==57114==    by 0x100006006: main (memory:3084)
==57114==
--57114-- UNKNOWN mach_msg unhandled MACH_SEND_TRAILER option
--57114-- UNKNOWN mach_msg unhandled MACH_SEND_TRAILER option (repeated 2 times)
--57114-- UNKNOWN mach_msg unhandled MACH_SEND_TRAILER option (repeated 4 times)
2015-11-09 20:22:03,302 VER-0 [default] Level : 0
2015-11-09 20:22:03,513 VER-0 [default] Logging parameters:
2015-11-09 20:22:03,519 VER-0 [default]     bin/raptorlang
==57114==
==57114== HEAP SUMMARY:
==57114==     in use at exit: 54,824 bytes in 452 blocks
==57114==   total heap usage: 1,495 allocs, 1,043 frees, 137,451 bytes allocated
==57114==
==57114== LEAK SUMMARY:
==57114==    definitely lost: 0 bytes in 0 blocks
==57114==    indirectly lost: 0 bytes in 0 blocks
==57114==      possibly lost: 0 bytes in 0 blocks
==57114==    still reachable: 19,914 bytes in 23 blocks
==57114==         suppressed: 34,910 bytes in 429 blocks
==57114== Reachable blocks (those to which a pointer was found) are not shown.
==57114== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==57114==
==57114== For counts of detected and suppressed errors, rerun with: -v
==57114== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 21 from 21)


            ELPP_argv_managed.push_back(make_unique<char[]>(arg_string.length()+1));
            std::copy(arg_string.begin(), arg_string.end(), ELPP_argv_managed.back().get());
            ELPP_argv_managed.back().get()[arg_string.length()+1] = '\0';

## Logging Rules

https://wiki.opendaylight.org/view/BestPractices/Logging_Best_Practices
https://jessehu.wordpress.com/2009/11/17/log4j-levels-all-trace-debug-info-warn-error-fatal-off/

- ERROR : error events that might still allow the application to continue running
    + might attempt recovery
    + might forcefully terminate
    + uncorrectable (or correctable) internal state inconsistency, or request-level error
    + primarily for system operators
- WARNING : potentially harmful situations
    + clearly-defined recovery strategy
    + primarily for operators and administrators
- INFO : informational messages that highlight the progress of the application at coarse-grained level
    + API-like contract (info and higher)
    + major state changes within software (init, operating, shutdown, shutdown, termination)
- DEBUG : fine-grained informational events that are most useful to debug an application
    + coarse diagnostic
    + interface contract with support entities
    + general programming concepts
    + indicate internal state transitions
- TRACE : finer-grained informational events than the DEBUG
    + internal state transitions in full detail
- FATAL : very severe error events that will presumably lead the application to abort

## Grammar

- using ANTLR to help develop grammar
- scoping
    + {} for blocks
    + : for single expressions
- still have an ambiguity issue with function call order (look at Haskell)
- explicit typing if wanted (modifiers?)

## Programming language for games

https://www.youtube.com/playlist?list=PLmV5I2fxaiCKfxMBrNsU1kgKJXD3PkyxO
http://crystal-lang.org/docs/
http://terralang.org/

algebraic data types

multiple mains --> multiple exes

- switch from C++ to another language
- cleaner version of C
- take good from C/C++
    + templates --> but make automatic generics (not a separate concept)
- llvm leads to less work for building a language
    + optimizing code
    + generating competent machine code (for many platforms)
- RAII (resource acquisition is initialization)
    + acquire in constructor, release in destructor (rule of 5 stuff)
    + not useful if everything has to follow the same pattern
    + exists because of exceptions, which add too much complexity
    + Go does not use exceptions (return error codes)
- not afraid of pointers
    + Rust has unsafe regions (useful for auditing program)
- inline initialization of objects/structs
- should have a string type
- debug statements for double free (manage in the runtime)
    + pointer vs reference types (initialization--no pointer to pointer)
- **type** keyword
- add support for debugging
    + knowledge about freeing freed memory
    + dereferencing freed memory
- syntax for pointer vs array version
- no manual memory allocation/deallocation
- not having multiple allocations for a single object
- static strings (const)
- optional types for null pointer checks
- no implicit type conversions
- named argument passing (at least default arguments)
- language should know about serialization
- compiler as an ongoing process (not started each time we want to)
- license
    + permissive (not an SFS)
    + bsd, nsf, public commons
- language creature comforts
    + nested block comments
    + no preprocessor (maybe include file, same statements as language statements)
- compile time solving (function evaluation)
- start to compiling to C or C++
- Go inheritance (composing data structures) -- not OOP
    + extend [other class] where the order matters

### A Programming Language for Games, talk #2 (Declarations and (Re)Factorability)

- comments are never run/debugged
- denote pure functions
- locally scoped functions
- local blocks (like braces in C++)
- no methods?
- automatically add type information
- same syntax for functions and lambdas
- capture variables
    + explicit hierarchical scoping
- block -> block w/ capture -> anon function -> named function
- async functions and code
    + explicit parallel loops
- don't force coding (i.e., due to bad programmers)
- co routines?
- data, code memory layout toold

### Demo: Base language, compile-time execution

- import modules (not including text)
- load files (source files)
    + doesn't have to be done in e.g. CMake
    + manifest
    + same syntax as the rest of the language
    + linking flags etc.
    + don't add layers if not necessary
- straightforward type inference
- Go types (no implicit conversions unless using base types (int vs uint8))
- implicit delete of pointer types (!*)
    + new and delete
- defer --> end of scope (reverse order as stated)
- each loop (not for)
- compile time asserts
- don't build complex type systems, add flexible checking system
- incremental compilation
- dependencies
- is it worth compiling to bytecode?
- tail calls
- cache friendly
- comments don't track with code
- https://en.wikipedia.org/wiki/Uniform_Function_Call_Syntax
- license: public domain or ... (MIT or ...)
- need a new OS
- support custom allocators
- embeddedable, full edit-and-continue
- IDE, tools, and debugger (visualizations)
- DLLs
- return type overloading
- optional and named parameters

### Demo: Iteration and arrays, uninitialized values, enums

(1: Build process; 2: Syntax changes; 3: Default values, explicit uninitialization; 4: Array types; 5: Iteration; 6: Enum types; 7: Inlining)

- specify build settings in the language syntax
    + can also be done from the command line
- he uses ^ and * for pointers; I like ^ with @
- initialized to default value by default (can be explicitly turned off with "---")
- array is a pointer and a size (struct behind the scenes)
- allow "remove" while iterating over array
- iterate over index and value
- nested continue and break labels
- iterate over enum names and values
- better control over inlining






