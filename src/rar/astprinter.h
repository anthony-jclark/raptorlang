
#ifndef _ASTPRINTER_HEADER_
#define _ASTPRINTER_HEADER_


#include "../general.h"
#include "visit.h"
#include "ast.h"

#include <string>


namespace raptor {
    namespace parser {

class ASTPrinter : public Visitor
{

    std::string ast_str;
    size_type tab_size;
    size_type cur_level;

public:

    explicit ASTPrinter(size_type tab=2) : tab_size(tab), cur_level(0) {};

public:

    const std::string& get_string(AST *n) {
        dynamic_cast<raptor::parser::BinaryOpASTN*>(n)->accept(*this);
        return this->ast_str;
    }

public:

    virtual void visit(IdentifierASTN &n) override final
    {
        this->ast_str += ws() + "ID --> " + n.name + "\n";
    }


    virtual void visit(IntegerASTN &n) override final
    {
        this->ast_str += ws() + "Integer with value = " + std::to_string(n.value) + "\n";
    }


    virtual void visit(FloatASTN &n) override final
    {
        this->ast_str += ws() + "Float with value = " + std::to_string(n.value) + "\n";
    }


    virtual void visit(BinaryOpASTN &n) override final
    {
        this->ast_str += ws() + "Binop :\n";

        ++this->cur_level;

        if (n.lhs) n.lhs->accept(*this);
        else this->ast_str += ws() + "<no-lhs>\n";

        this->ast_str += ws() + n.binop + "\n";

        if (n.rhs) n.rhs->accept(*this);
        else this->ast_str += ws() + "<no-rhs>\n";

        --this->cur_level;
    }

private:

    std::string ws(void)
    {
        return std::string(this->tab_size * this->cur_level, ' ');
    }

};


}
}



#endif

