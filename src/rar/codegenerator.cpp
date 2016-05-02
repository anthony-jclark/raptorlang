
#include "codegenerator.h"
#include "ast.h"
#include "../logging.h"



#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Intrinsics.h"



namespace raptor {
    namespace parser {


void CodeGenerator::visit(IdentifierASTN &n)
{
    (void)n;
}


void CodeGenerator::visit(IntegerASTN &n)
{
    // this->cur_val = llvm::ConstantFP::get(llvm::getGlobalContext(), llvm::APInt((int)n.value));
    this->cur_val = llvm::ConstantFP::get(llvm::getGlobalContext(), llvm::APFloat((double)n.value));
}


void CodeGenerator::visit(FloatASTN &n)
{
    this->cur_val = llvm::ConstantFP::get(llvm::getGlobalContext(), llvm::APFloat(n.value));
}


void CodeGenerator::visit(BinaryOpASTN &n)
{
    n.lhs->accept(*this);
    auto L = this->cur_val;
    n.rhs->accept(*this);
    auto R = this->cur_val;
    if (!L || !R) {
        this->cur_val = nullptr;
        return;
    }

    if (n.binop == "+")
        this->cur_val = this->ir_builder.CreateFAdd(L, R, "addtmp");
    else if (n.binop == "-")
        this->cur_val = this->ir_builder.CreateFSub(L, R, "subtmp");
    else if (n.binop == "*")
        this->cur_val = this->ir_builder.CreateFMul(L, R, "multmp");
    else if (n.binop == "/")
        this->cur_val = this->ir_builder.CreateFDiv(L, R, "divtmp");
    // else if (n.binop == "^") {
    //     std::vector<llvm::Value *> args{L, R};
    //     std::vector<llvm::Type  *> arg_types{L->getType(), R->getType()};
    //     auto fun = llvm::Intrinsic::getDeclaration(
    //         llvm_module.get(), llvm::Intrinsic::pow, arg_types);
    //     return ir_builder.CreateCall(fun, args);
    // }
    else {
        // error message here does not work with line/col numbers
        LOG_ERROR("Unexpected operator : " + n.binop);
        this->cur_val = nullptr;
    }
}


}
}

