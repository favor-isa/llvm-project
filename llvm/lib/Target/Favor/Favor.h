#ifndef LLVM_LIB_TARGET_FAVOR_FAVOR_H
#define LLVM_LIB_TARGET_FAVOR_FAVOR_H

#include "MCTargetDesc/FavorMCTargetDesc.h"
#include "llvm/Pass.h"
#include "llvm/Support/CodeGen.h"

namespace llvm {
  class FunctionPass;
  class FavorTargetMachine;

  FunctionPass *createFavorISelDagLegacy(FavorTargetMachine &TM,
                                     CodeGenOptLevel OptLevel);

  void initializeFavorDAGToDAGISelLegacyPass(PassRegistry &);
} // namespace llvm

#endif