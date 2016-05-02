

#ifndef _ASTVISIT_HEADER_
#define _ASTVISIT_HEADER_

namespace raptor {
    namespace parser {



class Visitable
{
    public: virtual void accept(class Visitor &v) = 0;
};

class Visitor
{

public:

    virtual void visit(class IdentifierASTN &n) = 0;
    virtual void visit(class IntegerASTN &n) = 0;
    virtual void visit(class FloatASTN &n) = 0;
    virtual void visit(class BinaryOpASTN &n) = 0;

};




}
}

#endif
