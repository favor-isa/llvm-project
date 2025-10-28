#include "FavorISelLowering.h"
#include "MCTargetDesc/FavorMCTargetDesc.h"
#include "FavorSubtarget.h"

using namespace llvm;

#define DEBUG_TYPE "favor-isel"

FavorTargetLowering::FavorTargetLowering(const TargetMachine &TM,
                                       const FavorSubtarget &STI)
    : TargetLowering(TM) {
  addRegisterClass(MVT::i32, &Favor::GPR64RegClass);

  computeRegisterProperties(STI.getRegisterInfo());
}

SDValue
FavorTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                bool isVarArg,
                                const SmallVectorImpl<ISD::OutputArg> &Outs,
                                const SmallVectorImpl<SDValue> &OutVals,
                                const SDLoc &dl, SelectionDAG &DAG) const {
  // Handle only integer return values
  // we need to copy the value to the v0 register.
  if (Outs.size() > 12) {
    report_fatal_error(
        "Only 12 return values are currently supported",
        false);
  }

  if (Outs.size() == 0) {
    return DAG.getNode(FavorISD::Ret, dl, MVT::Other, Chain);
  }

  SDValue Glue;
  SmallVector<SDValue, 3> RetOps(1, Chain);
  for (unsigned i = 0, e = Outs.size(); i != e; ++i) {
    const ISD::OutputArg &Out = Outs[i];
    const SDValue &OutVal = OutVals[i];
    if(!Out.ArgVT.isScalarInteger()) {
        report_fatal_error("Only integer return values are supported", false);
    }
    Chain = DAG.getCopyToReg(Chain, dl, Favor::A0 + i, OutVal, Glue);
    Glue = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(Favor::A0 + i, Out.VT));
  }
  RetOps[0] = Chain;
  RetOps.push_back(Glue);

  return DAG.getNode(FavorISD::Ret, dl, MVT::Other, RetOps);
}

SDValue FavorTargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
  SmallVectorImpl<SDValue> &InVals) const {
    return SDValue();
  }

bool FavorTargetLowering::CanLowerReturn(CallingConv::ID CallConv, MachineFunction &MF,
    bool IsVarArg,
    const SmallVectorImpl<ISD::OutputArg> &Outs,
    LLVMContext &Context, const Type *RetTy) const{
      return true;
}

const char *FavorTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case FavorISD::Ret:
    return "FavorISD::Ret";
  default:
    return "Unknown FavorISD::Node";
  }
}