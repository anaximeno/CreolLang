#ifndef _CREOL_AST_H
#define _CREOL_AST_H

#include <iostream>

namespace creol {
    enum NodeType {
        Statement,
        IfStatement,
        LoopStatement,
        Identifier,
        Literal
        // todo: add more...
    };
    
    class NodeAST {
    protected:
        NodeType Type;

    public:
        NodeType GetType();
        virtual std::string ToCode() = 0;
        virtual std::string GetRepr() = 0;
    };
};

#endif // _CREOL_AST_H