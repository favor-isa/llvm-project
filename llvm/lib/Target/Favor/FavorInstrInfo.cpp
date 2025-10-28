#include "FavorInstrInfo.h"
#include "MCTargetDesc/FavorMCTargetDesc.h"
#include "FavorTargetMachine.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

using namespace llvm;

#define DEBUG_TYPE "favor-instr-info"

#define GET_INSTRINFO_CTOR_DTOR
#include "FavorGenInstrInfo.inc"

FavorInstrInfo::FavorInstrInfo(const FavorSubtarget &STI) :
  FavorGenInstrInfo(STI, Favor::ADJCALLSTACKDOWN, Favor::ADJCALLSTACKUP),
  Subtarget(STI) { }