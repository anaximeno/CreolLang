#ifndef _CREOL_AST_H
#define _CREOL_AST_H

#include <iostream>
#include <vector>

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
        const NodeType& Type;

    public:
        const NodeType& GetType() const;
        virtual std::string ToCode() = 0;
        virtual std::string GetRepr() = 0;
    };

    class Sttmt : public NodeAST {
    public:
        virtual std::string ToCode() = 0;
        virtual std::string GetRepr() = 0;
    };

    class Expr : public Sttmt {
    public:
        virtual std::string ToCode() = 0;
        virtual std::string GetRepr() = 0;
    };
};

#endif // _CREOL_AST_H