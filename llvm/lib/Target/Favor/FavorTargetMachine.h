#ifndef LLVM_LIB_TARGET_FAVOR_FAVORTARGETMACHINE_H
#define LLVM_LIB_TARGET_FAVOR_FAVORTARGETMACHINE_H

#include "FavorSubtarget.h"
#include "FavorTargetObjectFile.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

    

class FavorTargetMachine : public CodeGenTargetMachineImpl {
    FavorSubtarget Subtarget;
    std::unique_ptr<TargetLoweringObjectFile> TLOF;

    static Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
        if (!RM)
            return Reloc::Static;
        return *RM;
    }

public:
    FavorTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
        StringRef FS, const TargetOptions &Options,
        std::optional<Reloc::Model> RM,
        std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
        bool JIT)
    : CodeGenTargetMachineImpl(T, 
            "e-p:64:64-i8:8:8-i16:16:16-i64:64",
            TT, CPU, FS, Options,
            getEffectiveRelocModel(RM),
            getEffectiveCodeModel(CM, CodeModel::Medium),
            OL
        ),
        Subtarget(TT, CPU, FS, *this),
        TLOF(new FavorTargetObjectFile())
    {
        initAsmInfo();
    }

  // ~FavorTargetMachine() override = default;

    TargetLoweringObjectFile *getObjFileLowering() const override {
        return TLOF.get();
    }

    const FavorSubtarget *getSubtargetImpl(const Function &F) const override {
        return &Subtarget;
    }

    TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
};

}

#endif