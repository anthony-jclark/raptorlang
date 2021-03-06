
#include "rar.h"
#include "ast.h"
#include "../logging.h"




namespace raptor {
    namespace parser {


// --------------------------------------------------------
// Utility functions for creating parser error messages
// --------------------------------------------------------
std::string rar::error_msg(std::string msg)
{
    std::ostringstream oss;
    oss << this->source_name << ':' << this->lexer.line_number << ':'
        << this->lexer.column_number << ": " << "Parsing Error :: " << msg;
    return oss.str();
}



// --------------------------------------------------------
// Helper method for parsing part of an expression
// - list atoms
// --------------------------------------------------------
ASTN_PTR rar::compute_atom()
{
    LOG_DEBUG("Beginning of 'rar::compute_atom'");

    auto cur_tok = this->lexer.cur_token;
    auto &nxt_tok = this->lexer.get_token();

    // Parse a parenthesized expression
    if (cur_tok.name == TOK::L_PAREN)
    {
        auto paren_expr = this->parse_expression();
        if (nxt_tok.name != TOK::R_PAREN)
        {
            LOG_ERROR(this->error_msg("Unmatched \"(\"."));
            return nullptr;
        }
        this->lexer.get_token();
        return paren_expr;
    }

    // Parse a number
    else if (cur_tok.name == TOK::INTEGER) {
        return std::make_unique<IntegerASTN>(std::stol(cur_tok.value));
    }

    // Parse a floating-point number
    else if (cur_tok.name == TOK::FLOAT) {
        return std::make_unique<FloatASTN>(std::stod(cur_tok.value));
    }

    // Check for an invalid token
    else {
        LOG_ERROR(this->error_msg("Unexpected token : " + cur_tok.to_string()));
        return nullptr;
    }
}



// --------------------------------------------------------
// Parse an expression
// - list expressions
// --------------------------------------------------------
ASTN_PTR rar::parse_expression(size_type min_prec)
{
    LOG_DEBUG("Beginning of 'rar::parse_expression'");

    auto lhs = this->compute_atom();

    while (true)
    {
        auto cur_tok = this->lexer.cur_token;
        if (OP_INFO.find(cur_tok.name) == OP_INFO.end()) break;

        auto opinfo = OP_INFO.at(cur_tok.name);
        if (opinfo.precedence < min_prec) break;

        auto next_min_prec = (opinfo.associativity == Associativity::LEFT)
            ? opinfo.precedence + 1
            : opinfo.precedence;

        auto op = cur_tok.value;
        cur_tok = this->lexer.get_token();
        auto rhs = parse_expression(next_min_prec);
        lhs = std::make_unique<BinaryOpASTN>(op, std::move(lhs), std::move(rhs));
    }

    return lhs;
}



// --------------------------------------------------------
// Top level parsing method (delegates to specific parsers)
// --------------------------------------------------------
void rar::parse(void)
{
    LOG_DEBUG("Beginning of 'rar::parse'");

    auto &token = this->lexer.get_token();
    while (token.name != TOK::END) {
        this->top_level.push_back(this->parse_expression());
    }
}


}
}


#include "codegenerator.h"
#include "astprinter.h"

//
// Test program --> should be deleted later
//
int main() {
    std::stringstream ss(
        "3 * (2 + 1) + 3 / 2 * 3 + 4\n"
        "11 + 22\n"
        "1 ^ 1"
    );

    auto parser = raptor::parser::rar(ss);
    parser.parse();

    auto printer = raptor::parser::ASTPrinter();
    LOG_INFO("\n" + printer.get_string(parser.top_level[0].get()) + "\n");

    auto codegen = raptor::parser::CodeGenerator(parser.source_name);
    codegen.generate(parser.top_level[0].get())->dump();

    return 0;
}