#include "FavorRegisterInfo.h"
#include "MCTargetDesc/FavorMCTargetDesc.h"
#include "FavorFrameLowering.h"

#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

using namespace llvm;

#define DEBUG_TYPE "favor-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "FavorGenRegisterInfo.inc"

using namespace llvm;

FavorRegisterInfo::FavorRegisterInfo() : FavorGenRegisterInfo(Favor::LA) {}

const MCPhysReg *
FavorRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
    static const MCPhysReg CSRList[] = {
        Favor::T0,
        Favor::T1,
        Favor::T2,
        Favor::T3,
        Favor::T4,
        Favor::T5,
        Favor::T6,
        Favor::T7,

        Favor::SP,
        Favor::FP,
        Favor::LA,
    };
    return CSRList;
}

BitVector FavorRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
    static const MCPhysReg ReservedRegs[] = {
        Favor::ZERO, Favor::SP
    };
    BitVector Reserved(getNumRegs());
    for (MCPhysReg Reg : ReservedRegs) {
        Reserved.set(Reg);
    }
    return Reserved;
}

bool FavorRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj, unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  return true;
}

Register FavorRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
    return Favor::FP;
}