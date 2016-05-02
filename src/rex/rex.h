
#ifndef _REX_HEADER_
#define _REX_HEADER_


#include "../general.h"


// --------------------------------------------------------
// Lexer tokens and function for printing tokens
// --------------------------------------------------------
#include "tokens.h"
// defines
//      enum class TOK
//      struct Token;
//      string and output stream functionality
//      utility functions for accessing keywords and operators


#include <iosfwd>



namespace raptor {
    namespace lexer {


// --------------------------------------------------------
// Lexing and tokenizing class
// --------------------------------------------------------
class rex
{

public:

    size_type line_number = 1;
    size_type column_number = 0;

    std::istream &token_stream;
    std::string stream_name;

    Token cur_token = {TOK::UNDEFINED, ""};

public:

    rex(std::istream &ts, std::string s="") :
        token_stream(ts),
        stream_name(s)
    {};

public:

    Token& get_token(void);

private:

    Token& process_word(char c);
    Token& process_number(char c);
    Token& process_string(char c, TOK t=TOK::STRING);
    Token& process_character(char c);
    Token& process_comment(char c);
    Token& process_punctuator(char c);

    std::istream& get(char& ch);
    void unget();

    std::string error_msg(std::string msg);
};

}
}


#endif


