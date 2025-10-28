#ifndef LLVM_LIB_TARGET_FAVOR_FAVORISELDAGTODAG_H
#define LLVM_LIB_TARGET_FAVOR_FAVORISELDAGTODAG_H

#include "FavorSubtarget.h"
#include "FavorTargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace llvm {
class FavorDAGToDAGISel final : public SelectionDAGISel {
  const FavorSubtarget *Subtarget;

public:
  explicit FavorDAGToDAGISel(FavorTargetMachine &TM, CodeGenOptLevel OptLevel)
      : SelectionDAGISel(TM, OptLevel) {}

  bool runOnMachineFunction(MachineFunction &MF) override;

private:
#include "FavorGenDAGISel.inc"

  void Select(SDNode *Node) override;
};
} // namespace llvm

#endif