#ifndef _CREOL_AST_NODE
#define _CREOL_AST_NODE

#include <llvm/IR/Value.h>

namespace creol {
    enum NodeType {
        // TODO
    };

    class NodeAST {
        public:
            virtual ~NodeAST() = default;
            virtual llvm::Value* codegen() = 0;
    };
};

#endif // _CREOL_AST_NODE