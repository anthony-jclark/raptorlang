
#ifndef _TOKENS_HEADER_
#define _TOKENS_HEADER_

#include <string>


enum class TOK
{
    NAME,//
    INTEGER,//
    FLOAT,//
    STRING,//
    CHARACTER,//
    COMMENT,//
    UNDEFINED,//
    END,//
    EXCLAIM,//!
    NOT_EQUAL,//!=
    HASH,//#
    DOLLAR,//$
    PERCENT,//%
    AMP,//&
    L_PAREN,//(
    R_PAREN,//)
    STAR,//*
    PLUS,//+
    COMMA,//,
    MINUS,//-
    PERIOD,//.
    SLASH,///
    COLON,//:
    SEMI,//;
    LESS,//<
    LESS2,//<<
    LESS_EQ,//<=
    EQUAL,//=
    EQUAL2,//==
    GREATER,//>
    GREATER_EQ,//>=
    GREATER2,//>>
    QUESTION,//?
    AT,//@
    L_SQUARE,//[
    R_SQUARE,//]
    CARET,//^
    AND,//and
    FALSE,//false
    IMPORT,//import
    LENGTH,//len
    MAIN,//main
    OR,//or
    PACKAGE,//package
    STRUCT,//struct
    TRUE,//true
    L_BRACE,//{
    PIPE,//|
    R_BRACE,//}
    TILDE,//~
};

struct Token{
    TOK name;
    std::string value;
};

// --------------------------------------------------------
// Function for printing tokens
// --------------------------------------------------------std::string TOK_toString(Token t);

// --------------------------------------------------------
// Utility function used to check for reserved words
// --------------------------------------------------------TOK TOK_getReserved(std::string word);

// --------------------------------------------------------
// Utility function used to check for punctuators
// --------------------------------------------------------TOK TOK_getPunctuator(std::istream& ts, char c);

#endif
