antlr4 raptor.g4 ; cantlr4 raptor*.java ; grun raptor block test.txt -tokens
rm *.tokens *.class *.java



## Grammar

- using ANTLR to help develop grammar
- scoping
    + {} for blocks
    + : for single expressions
- still have an ambiguity issue with function call order (look at Haskell)
- explicit typing if wanted (modifiers?)