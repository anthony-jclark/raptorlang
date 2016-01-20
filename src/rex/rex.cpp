
#include "../logging.h"
#include "rex.h"

#include <iostream>

// --------------------------------------------------------
// Utility functions for identifying alphanumerics and underscores
// --------------------------------------------------------
inline bool isalnumund(char c) { return std::isalnum(c) || c == '_'; }
inline bool isalund(char c) { return std::isalpha(c) || c == '_'; }


// --------------------------------------------------------
// Utility function used to process a "word"
// --------------------------------------------------------
Token _process_word(std::istream& ts, char c)
{
    DEBUG("Beginning");

    // Build a single word (letters, numbers, underscores)
    std::string word{c};
    while (ts.get(c) && isalnumund(c)) { word += c; }
    ts.unget();

    // Return the token
    auto res = TOK_getReserved(word);
    if (res == TOK::UNDEFINED)
        return {TOK::NAME, word};
    else
        return {res, word};
}

// --------------------------------------------------------
// Utility function used to process a "number"
// --------------------------------------------------------
Token _process_number(std::istream& ts, char c)
{
    DEBUG("Beginning");

    // Build a number string (dots and digits)
    std::string word;
    auto dot_count = 0;
    do {
        if (c == '.') ++dot_count;
        word += c;
    }
    while (ts.get(c) && (std::isdigit(c) || c == '.'));
    ts.unget();

    // Check for invalid floating-point number format
    if (dot_count >= 2) {
        ERROR("Lexing Error :: Badly formed float.");
        return {TOK::UNDEFINED, ""};
    }

    // Return a FLOAT or INT token
    else if (dot_count > 0)
        return {TOK::FLOAT, word};
    else
        return {TOK::INTEGER, word};
}


// --------------------------------------------------------
// Utility function used to process a "comment"
// --------------------------------------------------------
Token _process_string(std::istream& ts, char c, TOK t=TOK::STRING)
{
    DEBUG("Beginning");

    // Build the string until we hit the closing quote
    std::string word{c};
    char closer = c;
    while (ts.get(c) && c != closer) { word += c; }

    // Return the token
    if (word.back() == closer)
        return {t, word};
    else {
        ERROR("Lexing Error :: Never found the end of a string.")
        return {TOK::UNDEFINED, ""};
    }
}


// --------------------------------------------------------
// Utility function used to process a "comment"
// --------------------------------------------------------
Token _process_character(std::istream& ts, char c)
{
    DEBUG("Beginning");

    // Use _process_string to create the character
    auto t = _process_string(ts, c, TOK::CHARACTER);

    if (t.value.length() == 3)
        return t;
    else {
        ERROR("Lexing Error :: Invalid character.")
        return {TOK::UNDEFINED, ""};
    }
}

// --------------------------------------------------------
// Utility function used to process a "comment"
// --------------------------------------------------------
Token _process_comment(std::istream& ts, char c)
{
    DEBUG("Beginning");
    // Process multi-line comment
    if (c == '[') {
        while (ts.get(c))
            if (c == ']' && ts.get(c) && c == '#') break;
    }

    // Process single line comment
    else
        while (ts.get(c) && c != '\n');

    return get_token(ts);
}

// --------------------------------------------------------
// Tokenizer function
// --------------------------------------------------------
Token get_token(std::istream& ts)
{
    DEBUG("Beginning");
    // Skip white space
    char c;
    while (ts.get(c) && std::isspace(c));

    // Return END if istream ts empty
    if (!ts) return {TOK::END, ""};

    // NAME or a reserved keyword (starts with alpha or underscore)
    else if (isalund(c)) { return _process_word(ts, c); }

    // Number (INTEGER or FLOAT)
    else if (std::isdigit(c) || c == '.') { return _process_number(ts, c); }

    // STRING literal
    else if (c == '"') { return _process_string(ts, c); }

    // CHARACTER literal
    else if (c == '\'') { return _process_character(ts, c); }

    // Must be OPERATOR or PUNCTUATOR
    else {
        ERROR("Lexing Error :: Unexpected token: " << c);
        return { TOK::UNDEFINED, "" };
    }
}