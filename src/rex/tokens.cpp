//
// This file is generated by the 'tokens.py' script.
//

#include "tokens.h"
#include <string>
#include <array>
#include <unordered_map>
#include <iostream>


namespace raptor{
namespace lexer{


// --------------------------------------------------------
// Functions for printing Tokens and TOKs
// --------------------------------------------------------
std::string TOK_toString(TOK t)
{
    const auto NUM_TOK = 55;
    static const std::array<std::string, NUM_TOK> TOK_STRINGS = {{
        "NAME", "INTEGER", "FLOAT", "STRING", "CHARACTER", "COMMENT", 
        "UNDEFINED", "END", "EXCLAIM", "NOT_EQUAL", "HASH", "DOLLAR", 
        "PERCENT", "AMP", "L_PAREN", "R_PAREN", "STAR", "PLUS", "COMMA", 
        "MINUS", "PERIOD", "SLASH", "COLON", "SEMI", "LESS", "LESS2", 
        "LESS_EQ", "EQUAL", "EQUAL2", "GREATER", "GREATER_EQ", "GREATER2", 
        "QUESTION", "AT", "L_SQUARE", "R_SQUARE", "CARET", "ALIAS", "AND", 
        "FALSE", "FUNC", "IMPORT", "LENGTH", "LET", "MAIN", "OR", "PACKAGE", 
        "PROC", "SET", "STRUCT", "TRUE", "L_BRACE", "PIPE", "R_BRACE", 
        "TILDE", 
    }};
    return TOK_STRINGS[static_cast<unsigned>(t)];
}
std::string Token::toString() const {
    return "{" + TOK_toString(this->name) + ":\"" + this->value + "\"}";
}
std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << t.toString();
    return os;
}
std::ostream& operator<<(std::ostream& os, const TOK& t) {
    os << TOK_toString(t);
    return os;
}

// --------------------------------------------------------
// Utility function used to check for reserved words
// --------------------------------------------------------
std::unordered_map<std::string, TOK> getReservedList()
{
    const std::unordered_map<std::string, TOK> TOK_KEYWORDS = {
        {"true", TOK::TRUE},
        {"false", TOK::FALSE},
        {"main", TOK::MAIN},
        {"import", TOK::IMPORT},
        {"package", TOK::PACKAGE},
        {"struct", TOK::STRUCT},
        {"len", TOK::LENGTH},
        {"and", TOK::AND},
        {"or", TOK::OR},
        {"set", TOK::SET},
        {"let", TOK::LET},
        {"alias", TOK::ALIAS},
        {"func", TOK::FUNC},
        {"proc", TOK::PROC},
    };
    return TOK_KEYWORDS;
}
TOK getReservedTOK(std::string word)
{
    static const auto TOK_KEYWORDS = getReservedList();
    auto search = TOK_KEYWORDS.find(word);
    if (search != TOK_KEYWORDS.end()) {
        return search->second;
    }
    else {
        return TOK::UNDEFINED;
    }
}

// --------------------------------------------------------
// Utility function used to check for punctuators
// --------------------------------------------------------
std::unordered_map<std::string, TOK> getPunctuatorList()
{
    const std::unordered_map<std::string, TOK> TOK_PUNCTUATORS = {
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
    return TOK_PUNCTUATORS;
}
TOK getPunctuatorTOK(std::istream& ts, std::string &punc)
{
    static const auto MAX_PUNC_CHARS = 2;
    static const auto MAX_ALLOWED_CHARS = 2u;
    static_assert(MAX_PUNC_CHARS == MAX_ALLOWED_CHARS);
    static const auto TOK_PUNCTUATORS = getPunctuatorList();

    auto punc_size = 1u;
    auto return_token = TOK::UNDEFINED;
    auto search = TOK_PUNCTUATORS.find(punc);
    if (search != TOK_PUNCTUATORS.end()) {
        return_token = search->second;
    }

    // Check for longer punctuators (return the longest valid punc)
    for (auto i = punc_size + 1u; i <= MAX_ALLOWED_CHARS; ++i) {
        char c;
        if (ts.get(c)) {
            punc += c;
            search = TOK_PUNCTUATORS.find(punc);
            if (search != TOK_PUNCTUATORS.end()) {
                punc_size = i;
                return_token = search->second;
            }
        }
    }

    // Unget any unused characters
    for (auto i = MAX_ALLOWED_CHARS; i > punc_size; --i) {
        ts.unget();
        punc.pop_back();
    }
    return return_token;
}

}
}

