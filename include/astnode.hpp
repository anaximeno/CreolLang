#ifndef _CREOL_AST_NODE
#define _CREOL_AST_NODE

#include <llvm/IR/Value.h>

namespace creol {
    enum NodeType {
        // TODO
    };

    class Node {
        public:
            virtual ~Node() = default;

            virtual llvm::Value* codeGen() = 0;
    };
};

#endif // _CREOL_AST_NODE