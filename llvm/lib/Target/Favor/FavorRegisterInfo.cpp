#include "FavorRegisterInfo.h"
#include "MCTargetDesc/FavorMCTargetDesc.h"
#include "FavorFrameLowering.h"

#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

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
  
  MachineInstr &MI = *II;

  LLVM_DEBUG(errs() << "Favor: eliminateFrameIndex" << MI);
  MachineBasicBlock &MBB = *MI.getParent();
  MachineFunction &MF = *MI.getParent()->getParent();
  const TargetInstrInfo &TII = *MBB.getParent()->getSubtarget().getInstrInfo();
  auto DL = II->getDebugLoc();
  MachineRegisterInfo &RegInfo = MBB.getParent()->getRegInfo();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  uint64_t stackSize = MF.getFrameInfo().getStackSize();
  int64_t spOffset = MF.getFrameInfo().getObjectOffset(FrameIndex);

  Register Reg = RegInfo.createVirtualRegister(&Favor::GPR64RegClass);
  BuildMI(MBB, II, DL, TII.get(Favor::LOAD_I32), Reg)
    .addReg(Favor::SP)
    .addImm(spOffset);

  MI.getOperand(FIOperandNum).ChangeToRegister(Reg, false, false, false);
  //MI.getOperand(OpNo + 1).ChangeToImmediate(Offset);

  return false;
}

Register FavorRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
    return Favor::FP;
}