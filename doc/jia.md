
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






