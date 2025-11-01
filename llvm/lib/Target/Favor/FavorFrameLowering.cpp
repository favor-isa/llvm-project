#include "FavorFrameLowering.h"

#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#include "Favor.h"

using namespace llvm;

void FavorFrameLowering::emitPrologue(MachineFunction &MF,
                  MachineBasicBlock &MBB) const {
    MachineFrameInfo &MFI = MF.getFrameInfo();

    MachineBasicBlock::iterator MBBI = MBB.begin();

    const TargetInstrInfo &TII = *STI.getInstrInfo();
    const TargetRegisterInfo &RegInfo = *STI.getRegisterInfo();

    DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();

    uint64_t StackSize = MFI.getStackSize();
    if(StackSize == 0 && !MFI.adjustsStack()) return;

    // Adjust stack pointer.
    BuildMI(MBB, *MBBI, DL, TII.get(Favor::SUBI_U64), Favor::SP)
        .addReg(Favor::SP)
        .addImm(StackSize);

    // TODO: emit .cfi_ directives.
}

void FavorFrameLowering::emitEpilogue(MachineFunction &MF,
                  MachineBasicBlock &MBB) const {
    MachineFrameInfo &MFI = MF.getFrameInfo();

    // TODO: Does this work for ALL exits to the function?
    MachineBasicBlock::iterator MBBI = MBB.getFirstTerminator();

    const TargetInstrInfo &TII = *STI.getInstrInfo();
    const TargetRegisterInfo &RegInfo = *STI.getRegisterInfo();

    DebugLoc DL = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();

    uint64_t StackSize = MFI.getStackSize();
    if(!StackSize) return;

    // Adjust stack pointer.
    BuildMI(MBB, *MBBI, DL, TII.get(Favor::ADDI_U64), Favor::SP)
        .addReg(Favor::SP)
        .addImm(StackSize);
}