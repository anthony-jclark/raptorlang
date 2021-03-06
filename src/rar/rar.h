
//
// http://eli.thegreenplace.net
// /2012/08/02/parsing-expressions-by-precedence-climbing
//


#ifndef _RAR_HEADER_
#define _RAR_HEADER_

#include "../rex/rex.h"


#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <memory>


namespace raptor {
    namespace parser {




// Forward-delcaration of the AST class
class AST;



using namespace raptor::lexer;



// --------------------------------------------------------
// Parsing class
// --------------------------------------------------------
class rar
{

// friend class AST;
// friend class IdentifierASTN;
// template<typename T> friend class NumberASTN;
// friend class BinaryOpASTN;

public:

    std::istream& source_stream;
    std::string source_name;
    lexer::rex lexer;

    std::vector<std::unique_ptr<AST>> top_level;


private:

    //
    // An enum and struct for describing operators
    //
    enum class Associativity { LEFT, RIGHT };
    struct OperatorInfo {
        size_type precedence;
        Associativity associativity;
    };


public:

    const std::unordered_map<TOK, OperatorInfo> OP_INFO = {
        {TOK::PLUS,    {1, Associativity::LEFT}},
        {TOK::MINUS,   {1, Associativity::LEFT}},
        {TOK::STAR,    {2, Associativity::LEFT}},
        {TOK::SLASH,   {2, Associativity::LEFT}},
        {TOK::PERCENT, {2, Associativity::LEFT}},
        {TOK::CARET,   {3, Associativity::RIGHT}}
    };


public:

    rar(std::istream& ss, std::string s="") :
        source_stream(ss),
        source_name(s),
        lexer(source_stream, source_name)
    {};


public:

    void parse(void);

private:

    std::unique_ptr<AST> parse_expression(size_type min_prec=1);
    std::unique_ptr<AST> compute_atom(void);

    std::string error_msg(std::string msg);

};



}
}

#endif

