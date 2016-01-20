
#ifndef _REX_HEADER_
#define _REX_HEADER_

#include <iosfwd>
#include <string>


// --------------------------------------------------------
// Lexer tokens and function for printing tokens
// --------------------------------------------------------
#include "tokens.h"
// defines
//      struct Token;
//      enum class TOK
//      std::string TOK_STR(Token t);


// --------------------------------------------------------
// Tokenizer function
// --------------------------------------------------------
Token get_token(std::istream& is);

#endif

