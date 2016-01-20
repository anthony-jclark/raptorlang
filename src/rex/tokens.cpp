#include "tokens.h"
#include <string>
#include <array>
#include <unordered_map>
#include <iostream>


// --------------------------------------------------------
// Function for printing tokens
// --------------------------------------------------------std::string TOK_toString(Token t)
{
    static const std::array<std::string,50> TOK_STRINGS = {{
        "NAME", "INTEGER", "FLOAT", "STRING", "CHARACTER", "COMMENT", 
        "UNDEFINED", "END", "EXCLAIM", "NOT_EQUAL", "HASH", "DOLLAR", 
        "PERCENT", "AMP", "L_PAREN", "R_PAREN", "STAR", "PLUS", "COMMA", 
        "MINUS", "PERIOD", "SLASH", "COLON", "SEMI", "LESS", "LESS2", 
        "LESS_EQ", "EQUAL", "EQUAL2", "GREATER", "GREATER_EQ", "GREATER2", 
        "QUESTION", "AT", "L_SQUARE", "R_SQUARE", "CARET", "AND", "FALSE", 
        "IMPORT", "LENGTH", "MAIN", "OR", "PACKAGE", "STRUCT", "TRUE", 
        "L_BRACE", "PIPE", "R_BRACE", "TILDE", 
    }};
    return "{" + TOK_STRINGS[static_cast<unsigned>(t.name)] + ":" + t.value + "}";
}

// --------------------------------------------------------
// Utility function used to check for reserved words
// --------------------------------------------------------TOK TOK_getReserved(std::string word)
{
    static const std::unordered_map<std::string, TOK> TOK_KEYWORDS = {
        {"true", TOK::TRUE},
        {"false", TOK::FALSE},
        {"main", TOK::MAIN},
        {"import", TOK::IMPORT},
        {"package", TOK::PACKAGE},
        {"struct", TOK::STRUCT},
        {"len", TOK::LENGTH},
        {"and", TOK::AND},
        {"or", TOK::OR},
    };
    auto search = TOK_KEYWORDS.find(word);
    if (search != TOK_KEYWORDS.end()) {
        return search->second;
    }
    else {
        return TOK::UNDEFINED;
}}

// --------------------------------------------------------
// Utility function used to check for punctuators
// --------------------------------------------------------TOK TOK_getPunctuator(std::istream& ts, char c)
{
    static const unsigned MAX_PUNC_CHARS = 2;
    static_assert(MAX_PUNC_CHARS == 2);
    static const std::unordered_map<std::string, TOK> TOK_KEYWORDS = {
        {"!", TOK::EXCLAIM},
        {";", TOK::SEMI},
        {":", TOK::COLON},
        {",", TOK::COMMA},
        {".", TOK::PERIOD},
        {"?", TOK::QUESTION},
        {"+", TOK::PLUS},
        {"-", TOK::MINUS},
        {"*", TOK::STAR},
        {"/", TOK::SLASH},
        {"=", TOK::EQUAL},
        {"@", TOK::AT},
        {"$", TOK::DOLLAR},
        {"==", TOK::EQUAL2},
        {"!=", TOK::NOT_EQUAL},
        {"%", TOK::PERCENT},
        {"^", TOK::CARET},
        {"&", TOK::AMP},
        {"|", TOK::PIPE},
        {"~", TOK::TILDE},
        {"#", TOK::HASH},
        {"<", TOK::LESS},
        {"<<", TOK::LESS2},
        {"<=", TOK::LESS_EQ},
        {">", TOK::GREATER},
        {">>", TOK::GREATER2},
        {">=", TOK::GREATER_EQ},
        {"(", TOK::L_PAREN},
        {")", TOK::R_PAREN},
        {"{", TOK::L_BRACE},
        {"}", TOK::R_BRACE},
        {"[", TOK::L_SQUARE},
        {"]", TOK::R_SQUARE},
    };

    std::string word{c};
    TOK return_token = TOK::UNDEFINED;

    auto search = TOK_KEYWORDS.find(word);
    if (search != TOK_KEYWORDS.end()) {
        return_token = search->second;
    }

    if (ts.get(c)) {
        word += c;
        search = TOK_KEYWORDS.find(word);
        if (search != TOK_KEYWORDS.end())
            return_token = search->second;
        else
            ts.unget();
    }
    return return_token;
}
