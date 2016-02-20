
#include "ast.h"
#include "../logging.h"

namespace raptor {
    namespace parser {



// --------------------------------------------------------
// Identifier node methods
// --------------------------------------------------------
std::string IdentifierASTN::toString(size_type indent) const
{
    return ws(indent) + "ID --> " + name + "\n";
}




// --------------------------------------------------------
// Number node specialization methods
// --------------------------------------------------------
template<>
llvm::Value* NumberASTN<double>::codegen()
{
    return llvm::ConstantFP::get(llvm::getGlobalContext(),
        llvm::APFloat(number));
}

template<>
std::string NumberASTN<double>::toString(size_type indent) const
{
    std::ostringstream oss;
    oss << ws(indent) + "Number with value = " << number << "\n";
    return oss.str();
}




// --------------------------------------------------------
// Binary Operator node methods
// --------------------------------------------------------
llvm::Value* BinaryOpASTN::codegen()
{
    auto L = lhs->codegen();
    auto R = rhs->codegen();
    if (!L || !R) return nullptr;

    if (binop == "+")
        return par->ir_builder.CreateFAdd(L, R, "addtmp");
    else if (binop == "-")
        return par->ir_builder.CreateFSub(L, R, "subtmp");
    else if (binop == "*")
        return par->ir_builder.CreateFMul(L, R, "multmp");
    else if (binop == "/")
        return par->ir_builder.CreateFDiv(L, R, "divtmp");
    // else if (binop == "^") {
    //     std::vector<llvm::Value *> args{L, R};
    //     std::vector<llvm::Type  *> arg_types{L->getType(), R->getType()};
    //     auto fun = llvm::Intrinsic::getDeclaration(
    //         par->llvm_module.get(), llvm::Intrinsic::pow, arg_types);
    //     return par->ir_builder.CreateCall(fun, args);
    // }
    else {
        // error message here does not work with line/col numbers
        // LOG_ERROR(par->error_msg("Unexpected operator : " + binop));
        return nullptr;
    }
}

std::string BinaryOpASTN::toString(size_type indent) const
{
    return ws(indent) + "Binop :\n"
        + (lhs ? lhs->toString(indent + 1) : ws(indent + 1) + "<no-lhs>\n")
        + ws(indent + 1) + binop + "\n"
        + (rhs ? rhs->toString(indent + 1) : ws(indent + 1) + "<no-rhs>\n");
}




}
}
