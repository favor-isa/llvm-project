#ifndef LLVM_LIB_TARGET_FAVOR_FAVORTARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_FAVOR_FAVORTARGETOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {
class TargetMachine;
class MCContext;
class FavorTargetObjectFile final : public TargetLoweringObjectFileELF {
public:
    public:
  void Initialize(MCContext &Ctx, const TargetMachine &TM) override;
};
}

#endif