#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

namespace llvm {
    llvm::Target &getTheFavorTarget() {
        static Target TheFavorTarget;
        return TheFavorTarget;
    }
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFavorTargetInfo() {
    llvm::RegisterTarget<llvm::Triple::favor> X(llvm::getTheFavorTarget(),
    "favor", "FaVOR", "Favor");
}

extern "C" void LLVMInitializeFavorTarget() {
    // TODO: Add initialize target
}