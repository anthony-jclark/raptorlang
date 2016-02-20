
#ifndef _AST_HEADER_
#define _AST_HEADER_

#include "rar.h"

#include <iosfwd>


namespace raptor {
    namespace parser {




// Forward-declaration of raptor::parser::rar
class rar;




// Get spaces
inline std::string ws(size_type indent) {
    return std::string(indent, ' ');
}


// --------------------------------------------------------
// Base class for the abstract syntax tree
// --------------------------------------------------------
class AST {
protected:
    rar &par;
public:
    explicit AST(rar &p) : par(p) {}
    virtual ~AST() = default;
    virtual llvm::Value* codegen() = 0;
    virtual std::string toString(size_type indent) const = 0;
};
using ASTN_PTR = std::unique_ptr<AST>;




// --------------------------------------------------------
// Identifier (concrete AST node)
// --------------------------------------------------------
class IdentifierASTN : public AST {
    std::string name;
public:
    IdentifierASTN(rar &p, const std::string& id) : AST(p), name(id) {};
    virtual std::string toString(size_type indent) const override final;
};




// --------------------------------------------------------
// Number (concrete AST)
// --------------------------------------------------------

// using INTEGER = long;
using INTEGER = double;
using FLOAT = double;

template<typename T>
class NumberASTN : public AST {
    T number;
public:
    NumberASTN(rar &p, T val) : AST(p), number(val) {};
    virtual llvm::Value* codegen() override final;
    virtual std::string toString(size_type indent) const override final;
};

// class DoubleASTN : public NumberASTN {
//     double number;
// public:
//     DoubleASTN(rar &p, double n) : NumberASTN(p), number(n) {}
//     virtual llvm::Value* codegen() override final;
//     virtual std::string toString(size_type indent) const override final;
// };




// --------------------------------------------------------
// Binary operator (concrete AST node)
// --------------------------------------------------------
class BinaryOpASTN : public AST {
    std::string binop;
    ASTN_PTR lhs, rhs;
public:
    BinaryOpASTN(rar &p, std::string op, ASTN_PTR l, ASTN_PTR r) :
        AST(p),
        binop(op),
        lhs(std::move(l)),
        rhs(std::move(r))
    {};
    virtual llvm::Value* codegen() override final;
    virtual std::string toString(size_type indent) const override final;
};




}
}

#endif

