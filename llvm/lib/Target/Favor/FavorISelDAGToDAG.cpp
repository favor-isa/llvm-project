#include "FavorISelDAGToDAG.h"
#include "FavorSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Pass.h"
#include "llvm/Support/CodeGen.h"

using namespace llvm;

#define DEBUG_TYPE "nova-isel"

namespace {
class FavorDAGToDAGISelLegacy : public SelectionDAGISelLegacy {
public:
  static char ID;
  FavorDAGToDAGISelLegacy(FavorTargetMachine &TM, CodeGenOptLevel OptLevel)
      : SelectionDAGISelLegacy(
            ID, std::make_unique<FavorDAGToDAGISel>(TM, OptLevel)) {}
};
} // namespace

char FavorDAGToDAGISelLegacy::ID = 0;

INITIALIZE_PASS(FavorDAGToDAGISelLegacy, DEBUG_TYPE, "favor-isel", false, false)


FunctionPass *llvm::createFavorISelDagLegacy(FavorTargetMachine &TM,
                                     CodeGenOptLevel OptLevel) {
  return new FavorDAGToDAGISelLegacy(TM, OptLevel);
}

bool FavorDAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget =
      &static_cast<const FavorSubtarget &>(MF.getSubtarget<FavorSubtarget>());
  return SelectionDAGISel::runOnMachineFunction(MF);
}

bool FavorDAGToDAGISel::selectAddrFrameIndex(SDValue Addr, SDValue &Base,
                                              SDValue &Offset) const {
                                                
  // Explanation for what this does:
  // When eliminating FrameIndex in eliminateFrameIndex, we need two operands
  // in our machine code: The stack pointer (a register), plus the offset from
  // it (a constant).
  //
  // So, we need to generate a MachineInstr that has these properties.
  //
  // To do so, we create a ComplexPattern for our addresses, and then match
  // on these to create a load instruction.
  //
  // Although... maybe we can do this more simply...?
  //
  // Yes we can!
  //
  // For now, to keep things simple, we simply directly replace the FrameIndex
  // in our generated Loads/Stores with the Offset. We can do this because we
  // are essentially using a special instruction for the FrameIndex implementation.
  //
  // If we ever make our load/stores more generic, then the better approach will
  // be to use a ComplexPattern plus this idea.
  if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Addr)) {
    EVT ValTy = Addr.getValueType();

    Base   = CurDAG->getTargetFrameIndex(FIN->getIndex(), ValTy);
    Offset = CurDAG->getTargetConstant(0, SDLoc(Addr), ValTy);
    return true;
  }
  return false;
}

void FavorDAGToDAGISel::Select(SDNode *Node) {
  // Implement the selection logic here.
  // This is where you would match the SelectionDAG nodes to the target
  // instructions. For example, you might want to match a specific node type and
  // then create a corresponding machine instruction.

  auto &Ctx = *CurDAG->getContext();

  // What this does (afaiii) is essentially say "we always successfully match on FrameIndex."
  //
  // That is not, per-se, true, but until we get slightly more sophisticated patterns
  // it is fine...
  if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Node)) {
    return;
  }

  // Example: if (Node->getOpcode() == ISD::ADD) { ... }
  // This is just a placeholder for the actual implementation.
  SelectCode(Node);
}