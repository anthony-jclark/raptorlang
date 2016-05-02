
#ifndef _AST_HEADER_
#define _AST_HEADER_


#include "../general.h"
#include "visit.h"

#include <iosfwd>
#include <string>




namespace raptor {
    namespace parser {





// --------------------------------------------------------
// Base class for the abstract syntax tree
// --------------------------------------------------------
class AST : public Visitable
{
public:
    virtual ~AST() = default;
};
using ASTN_PTR = std::unique_ptr<AST>;




// --------------------------------------------------------
// Identifier (concrete AST node)
// --------------------------------------------------------
class IdentifierASTN : public AST
{
public:
    std::string name;
    explicit IdentifierASTN(const std::string& id) : name(id) {};
    virtual void accept(Visitor &v) override final { v.visit(*this); }
};




// --------------------------------------------------------
// Integer (concrete AST)
// --------------------------------------------------------
class IntegerASTN : public AST
{
public:
    Integer value;
    explicit IntegerASTN(Integer val) : value(val) {};
    virtual void accept(Visitor &v) override final { v.visit(*this); }
};




// --------------------------------------------------------
// Float (concrete AST)
// --------------------------------------------------------
class FloatASTN : public AST
{
public:
    Float value;
    explicit FloatASTN(Float val) : value(val) {};
    virtual void accept(Visitor &v) override final { v.visit(*this); }
};




// --------------------------------------------------------
// Binary operator (concrete AST node)
// --------------------------------------------------------
class BinaryOpASTN : public AST
{
public:
    std::string binop;
    ASTN_PTR lhs, rhs;
    BinaryOpASTN(std::string op, ASTN_PTR l, ASTN_PTR r) :
        binop(op),
        lhs(std::move(l)),
        rhs(std::move(r))
    {};
    virtual void accept(Visitor &v) override final { v.visit(*this); }
};




}
}

#endif

