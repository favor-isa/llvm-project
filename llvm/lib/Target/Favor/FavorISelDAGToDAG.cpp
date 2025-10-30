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

void FavorDAGToDAGISel::Select(SDNode *Node) {
  // Implement the selection logic here.
  // This is where you would match the SelectionDAG nodes to the target
  // instructions. For example, you might want to match a specific node type and
  // then create a corresponding machine instruction.

  if (FrameIndexSDNode *FIN = dyn_cast<FrameIndexSDNode>(Node)) {
    //EVT ValTy = Node->getValueType();

    //Base   = CurDAG->getTargetFrameIndex(FIN->getIndex(), ValTy);
    //Offset = CurDAG->getTargetConstant(0, SDLoc(Addr), ValTy);
    //SDValue Offset = CurDAG->getTargetConstant(0, FIN->getDebugLoc(), )
    //CurDAG->getNode(FavorISD::FRAME_INDEX, FIN->getDebugLoc(), MVT::Other);
    //ReplaceNode(FIN, FIN);
    //return;
  }

  // Example: if (Node->getOpcode() == ISD::ADD) { ... }
  // This is just a placeholder for the actual implementation.
  SelectCode(Node);
}