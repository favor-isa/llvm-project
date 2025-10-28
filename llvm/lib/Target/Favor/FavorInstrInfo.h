#ifndef LLVM_LIB_TARGET_FAVOR_FAVORINSTRINFO_H
#define LLVM_LIB_TARGET_FAVOR_FAVORINSTRINFO_H

#include "Favor.h"
#include "FavorRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "FavorGenInstrInfo.inc"

namespace llvm {
class FavorSubtarget;

class FavorInstrInfo : public FavorGenInstrInfo {
public:
  explicit FavorInstrInfo(const FavorSubtarget &STI);
protected:
  const FavorSubtarget &Subtarget;
};
} // end namespace llvm

#endif