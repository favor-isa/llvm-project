#include "FavorMCTargetDesc.h"
#include "TargetInfo/FavorTargetInfo.h"

#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
// Defines the InitFavorMCRegisterInfo function
#include "FavorGenRegisterInfo.inc"

static MCRegisterInfo* createFavorMCRegisterInfo(const Triple &TT) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitFavorMCRegisterInfo(X, Favor::LA);
    return X;
}

extern "C" void LLVMInitializeFavorTargetMC() {
  Target *T =  &getTheFavorTarget();
  TargetRegistry::RegisterMCRegInfo(*T, createFavorMCRegisterInfo);
}