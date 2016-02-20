
- rex
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
    + **Operators** are used in expressions to describe operations involving one or more operands. For example, the expression a + b uses the + operator to add the two operands a and b. 
    + **Punctuators** are for grouping and separating.
    + Operator or punctuator
        * Alternative representation
        * &&  and
        * |   bitor
        * ||  or
        * ^   xor
        * ~   compl
        * &   bitand
        * &=  and_eq
        * |=  or_eq
        * ^=  xor_eq
        * !   not
        * !=  not_eq