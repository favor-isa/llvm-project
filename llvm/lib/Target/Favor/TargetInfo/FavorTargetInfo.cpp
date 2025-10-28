#include "Favor.h"
#include "FavorTargetMachine.h"

#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"
#include "llvm/PassRegistry.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"
#include "llvm/CodeGen/TargetPassConfig.h"

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
    RegisterTargetMachine<FavorTargetMachine> X(llvm::getTheFavorTarget());

    initializeFavorDAGToDAGISelLegacyPass(*PassRegistry::getPassRegistry());
}

namespace {
class FavorPassConfig : public TargetPassConfig {
public:
    FavorPassConfig(FavorTargetMachine &TM, PassManagerBase &PM)
        : TargetPassConfig(TM, PM) {}

    FavorTargetMachine &getFavorTargetMachine() const {
        return getTM<FavorTargetMachine>();
    }
    bool addInstSelector() override {
        addPass(createFavorISelDagLegacy(getFavorTargetMachine(), getOptLevel()));
        return false;
    }
    void addPreEmitPass() override {}
};
} // namespace

TargetPassConfig *FavorTargetMachine::createPassConfig(PassManagerBase &PM) {
    return new FavorPassConfig(*this, PM);
}
