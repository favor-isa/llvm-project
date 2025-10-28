#ifndef LLVM_LIB_TARGET_FAVOR_FAVORREGISTERINFO_H
#define LLVM_LIB_TARGET_FAVOR_FAVORREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "FavorGenRegisterInfo.inc"

namespace llvm {

class FavorRegisterInfo final : public FavorGenRegisterInfo {
public:
    FavorRegisterInfo();
    const MCPhysReg* getCalleeSavedRegs(const MachineFunction *MF) const override;

    BitVector getReservedRegs(const MachineFunction &MF) const override;

    bool eliminateFrameIndex(MachineBasicBlock::iterator II,
        int SPAdj, unsigned FIOperandNum,
        RegScavenger *RS = nullptr) const override;

    Register getFrameRegister(const MachineFunction &MF) const override;
};

}

#endif