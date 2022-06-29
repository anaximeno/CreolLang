#ifndef _CREOL_STATEMENT
#define _CREOL_STATEMENT

#include <llvm/IR/Value.h>
#include "astnode.hpp"

namespace creol {
    /** Represents a statement. */
    class StmtAST : public NodeAST {
        public:
            virtual ~StmtAST() = default;
    };
};

#endif // _CREOL_STATEMENT