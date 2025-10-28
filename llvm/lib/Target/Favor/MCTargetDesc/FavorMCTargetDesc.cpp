#include "FavorMCTargetDesc.h"
#include "TargetInfo/FavorTargetInfo.h"

#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "MCTargetDesc/FavorMCAsmInfo.h"
#include "MCTargetDesc/FavorMCInstPrinter.h"
#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "FavorGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
// Defines the InitFavorMCRegisterInfo function
#include "FavorGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "FavorGenSubtargetInfo.inc"


static MCRegisterInfo* createFavorMCRegisterInfo(const Triple &TT) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitFavorMCRegisterInfo(X, Favor::LA);
    return X;
}

static MCAsmInfo* createFavorMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT, const MCTargetOptions &Options) {
    MCAsmInfo *X = new FavorMCAsmInfo(TT);
    unsigned SP = MRI.getDwarfRegNum(Favor::SP, true);
    MCCFIInstruction Inst = MCCFIInstruction::createDefCfaRegister(nullptr, SP);
    X->addInitialFrameState(Inst);
    return X;
}

static MCInstPrinter* createFavorMCInstPrinter(const Triple &T, unsigned SyntaxVariant, const MCAsmInfo &MAI, const MCInstrInfo &MII, const MCRegisterInfo &MRI) {
  return new FavorInstPrinter(MAI, MII, MRI);
}

static MCInstrInfo* createFavorMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitFavorMCInstrInfo(X);
  return X;
}

static MCSubtargetInfo* createFavorSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  if (CPU.empty())
      CPU = "generic";
  return createFavorMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

extern "C" void LLVMInitializeFavorTargetMC() {
  Target *T =  &getTheFavorTarget();
  TargetRegistry::RegisterMCRegInfo(*T, createFavorMCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(*T, createFavorSubtargetInfo);
  TargetRegistry::RegisterMCInstrInfo(*T, createFavorMCInstrInfo);
  TargetRegistry::RegisterMCAsmInfo(*T, createFavorMCAsmInfo);
  TargetRegistry::RegisterMCInstPrinter(*T, createFavorMCInstPrinter);
}