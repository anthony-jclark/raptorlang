
#include "../logging.h"
#include "rex.h"

#include <istream>
#include <sstream>

namespace raptor {
    namespace lexer {

// --------------------------------------------------------
// Utility functions for identifying alphanumerics and underscores
// --------------------------------------------------------
inline bool isalnumund(char c) { return std::isalnum(c) || c == '_'; }
inline bool isalund(char c) { return std::isalpha(c) || c == '_'; }


// --------------------------------------------------------
// Utility functions for creating lexer error messages
// --------------------------------------------------------
std::string rex::error_msg(std::string msg)
{
    std::ostringstream oss;
    oss << this->stream_name << ':' << this->line_number << ':'
        << this->column_number << ": " << "Lexing Error :: " << msg;
    return oss.str();
}


// --------------------------------------------------------
// Utility function used to grab a single character from the input
// --------------------------------------------------------
std::istream& rex::get(char& ch)
{
    auto &stream_ret = this->token_stream.get(ch);
    this->column_number++;
    if (ch == '\n') {
        this->column_number = 0;
        this->line_number++;
    }
    return stream_ret;
}
void rex::unget() {
    this->token_stream.unget();
    this->column_number--;
}


// --------------------------------------------------------
// Utility function used to process a "word"
// --------------------------------------------------------
Token& rex::process_word(char c)
{
    LOG_DEBUG("Beginning of 'rex::process_word'");

    // Build a single word (letters, numbers, underscores)
    std::string word{c};
    while (this->get(c) && isalnumund(c)) { word += c; }
    this->unget();

    // Return the token
    auto res = getReservedTOK(word);
    if (res == TOK::UNDEFINED)
        return (this->cur_token = {TOK::NAME, word});
    else
        return (this->cur_token = {res, word});
}

// --------------------------------------------------------
// Utility function used to process a number
// --------------------------------------------------------
Token& rex::process_number(char c)
{
    LOG_DEBUG("Beginning of 'rex::process_number'");

    // Build a number string (dots and digits)
    std::string word;
    auto dot_count = 0;
    do {
        if (c == '.') ++dot_count;
        word += c;
    }
    while (this->get(c) && (std::isdigit(c) || c == '.'));
    this->unget();

    // Check for invalid floating-point number format
    if (dot_count >= 2) {
        LOG_ERROR(this->error_msg("Badly formed float."));
        return (this->cur_token = {TOK::UNDEFINED, ""});
    }

    // Return a FLOAT or INT token
    else if (dot_count > 0)
        return (this->cur_token = {TOK::FLOAT, word});
    else
        return (this->cur_token = {TOK::INTEGER, word});
}


// --------------------------------------------------------
// Utility function used to process a string (or character)
// --------------------------------------------------------
Token& rex::process_string(char c, TOK t)
{
    LOG_DEBUG("Beginning of 'rex::process_string'");

    // Build the string until we hit the closing quote
    std::string word{c};
    char quote_style = c;
    while (this->get(c) && c != quote_style) { word += c; }
    word += c;

    // Return the token
    if (word.back() == quote_style)
        return (this->cur_token = {t, word});
    else {
        LOG_ERROR(this->error_msg("Never found the end of a string."));
        return (this->cur_token = {TOK::UNDEFINED, ""});
    }
}


// --------------------------------------------------------
// Utility function used to process a character
// --------------------------------------------------------
Token& rex::process_character(char c)
{
    static const auto CHARACTER_LENGTH = 3;

    LOG_DEBUG("Beginning of 'rex::process_character'");

    // Use process_string to create the character
    auto t = this->process_string(c, TOK::CHARACTER);

    if (t.value.length() == CHARACTER_LENGTH)
        return (this->cur_token = t);
    else {
        LOG_ERROR(this->error_msg("Invalid character."));
        return (this->cur_token = {TOK::UNDEFINED, ""});
    }
}

// --------------------------------------------------------
// Utility function used to process a comment
// --------------------------------------------------------
Token& rex::process_comment(char c)
{
    LOG_DEBUG("Beginning of 'rex::process_comment'");

    std::string word{c};

    if (!this->get(c)) return (this->cur_token = {TOK::UNDEFINED, ""});
    word += c;

    // Process multi-line comment
    if (c == '*') {
        while (this->get(c)) {
            word += c;
            if (c == '*' && this->get(c) && c == '/') {
                word += c;
                break;
            }
        }
    }

    // Process single line comment
    else
        while (this->get(c) && c != '\n') word += c;

    return (this->cur_token = {TOK::COMMENT, word});
}

// --------------------------------------------------------
// Utility function used to process a punctuator
// --------------------------------------------------------
Token& rex::process_punctuator(char c)
{
    LOG_DEBUG("Beginning of 'rex::process_punctuator'");

    std::string word{c};
    auto punc = getPunctuatorTOK(this->token_stream, word);
    if (punc == TOK::UNDEFINED) {
        LOG_ERROR(this->error_msg("Unexpected token: " + word));
        return (this->cur_token = { TOK::UNDEFINED, "" });
    }
    else
        return (this->cur_token = {punc, word});
}

// --------------------------------------------------------
// Tokenizer function
// --------------------------------------------------------
Token& rex::get_token()
{
    LOG_DEBUG("Beginning of 'rex::get_token'");

    // Skip white space
    char c;
    while (this->get(c) && std::isspace(c));

    // Return END if istream token_stream empty
    if (!this->token_stream) return (this->cur_token = {TOK::END, ""});

    // NAME or a reserved keyword (starts with alpha or underscore)
    else if (isalund(c)) { return this->process_word(c); }

    // Number (INTEGER or FLOAT)
    else if (std::isdigit(c)) { return this->process_number(c); }

    // STRING literal
    else if (c == '"') { return this->process_string(c); }

    // CHARACTER literal
    else if (c == '\'') { return this->process_character(c); }

    // COMMENT
    else if (c == '/' && (   this->token_stream.peek() == '/'
                          || this->token_stream.peek() == '*')) {
        return this->process_comment(c);
    }

    // Must be a PUNCTUATOR (or undefined)
    else { return this->process_punctuator(c); }
}

}
}
