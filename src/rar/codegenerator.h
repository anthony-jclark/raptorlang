
#ifndef _CODEGEN_HEADER_
#define _CODEGEN_HEADER_


#include "../general.h"
#include "visit.h"
#include "ast.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"






namespace raptor {
    namespace parser {


class CodeGenerator : public Visitor
{

    llvm::IRBuilder<> ir_builder;
    std::unique_ptr<llvm::Module> llvm_module;
    std::map<std::string, llvm::Value *> NamedValues;

    llvm::Value *cur_val;

public:

    CodeGenerator(std::string &prog_name) :
        ir_builder(llvm::getGlobalContext()),
        llvm_module(llvm::make_unique<llvm::Module>(prog_name.c_str(),
            llvm::getGlobalContext()))
    {};

public:

    auto generate(AST *n) {
        dynamic_cast<raptor::parser::BinaryOpASTN*>(n)->accept(*this);
        return this->cur_val;
    }

public:

    virtual void visit(IdentifierASTN &n) override final;
    virtual void visit(IntegerASTN &n) override final;
    virtual void visit(FloatASTN &n) override final;
    virtual void visit(BinaryOpASTN &n) override final;

};


}
}



#endif

