#include "FavorISelLowering.h"
#include "MCTargetDesc/FavorMCTargetDesc.h"
#include "FavorSubtarget.h"

using namespace llvm;

#define DEBUG_TYPE "favor-isel"

// Helper function stolen from Mips
static unsigned
addLiveIn(MachineFunction &MF, unsigned PReg, const TargetRegisterClass *RC)
{
  Register VReg = MF.getRegInfo().createVirtualRegister(RC);
  MF.getRegInfo().addLiveIn(PReg, VReg);
  return VReg;
}

FavorTargetLowering::FavorTargetLowering(const TargetMachine &TM,
                                       const FavorSubtarget &STI)
    : TargetLowering(TM) {
  addRegisterClass(MVT::i32, &Favor::GPR64RegClass);
  addRegisterClass(MVT::i64, &Favor::GPR64RegClass);

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
  SmallVector<SDValue> RetOps(1, Chain);
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

    // Some notes:
    // CLI.Outs is the arguments
    // CLI.Ins is the return values
  
    SelectionDAG &DAG = CLI.DAG;
    SDLoc DL = CLI.DL;
    SDValue Chain = CLI.Chain;
    auto PtrVT = getPointerTy(DAG.getDataLayout());

    SDValue InGlue;

    SmallVector<SDValue> Ops;
    // Need to be added later due to pattern setup
    SmallVector<SDValue> RegOps;

    unsigned i = 0;
    for(auto &Out : CLI.Outs) {
      if(!Out.VT.isScalarInteger()) {
        report_fatal_error("Only integer arguments are supported", false);
      }
      
      Chain = DAG.getCopyToReg(Chain, DL, Favor::A0 + i, CLI.OutVals[i], InGlue);
      InGlue = Chain.getValue(1);
      
      RegOps.push_back(DAG.getRegister(Favor::A0 + i, Out.VT));

      i += 1;
    }

    SDValue Callee = CLI.Callee;
    if (GlobalAddressSDNode *G = dyn_cast<GlobalAddressSDNode>(Callee)) {
      Callee = DAG.getTargetGlobalAddress(G->getGlobal(), DL, PtrVT, 0);
    }
    else if (ExternalSymbolSDNode *E = dyn_cast<ExternalSymbolSDNode>(Callee)) {
      Callee = DAG.getTargetExternalSymbol(E->getSymbol(), PtrVT);
    }

    Ops.push_back(Chain);
    Ops.push_back(Callee);

    for(auto Op : RegOps) { 
      Ops.push_back(Op);
    }

    Chain = DAG.getNode(FavorISD::CALL, DL, MVT::Other, Ops);
    // TODO: Add Call seq end

    // Return values
    for (unsigned i = 0; i != CLI.Ins.size(); ++i) {
      const ISD::InputArg &In = CLI.Ins[i];
      if(!In.VT.isScalarInteger()) {
          report_fatal_error("Only integer argument types are supported", false);
      }

      unsigned Reg = addLiveIn(DAG.getMachineFunction(), Favor::A0 + i, getRegClassFor(In.VT));
      SDValue InVal = DAG.getCopyFromReg(Chain, DL, Reg, In.VT);
      //Glue = Chain.getValue(1);
      InVals.push_back(InVal);
    }
    return Chain;
}

bool FavorTargetLowering::CanLowerReturn(CallingConv::ID CallConv, MachineFunction &MF,
    bool IsVarArg,
    const SmallVectorImpl<ISD::OutputArg> &Outs,
    LLVMContext &Context, const Type *RetTy) const{
      return true;
}



SDValue
FavorTargetLowering::LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
  bool isVarArg,
  const SmallVectorImpl<ISD::InputArg> & Ins,
  const SDLoc & dl, SelectionDAG & DAG,
  SmallVectorImpl<SDValue> & InVals) const {

  if(isVarArg) { report_fatal_error("VarArgs not supported."); }

  if (Ins.size() == 0) {
    return Chain;
  }

  SDValue Glue;
  //SmallVector<SDValue> ArgOps(1, Chain);
  for (unsigned i = 0, e = Ins.size(); i != e; ++i) {
    const ISD::InputArg &In = Ins[i];
    if(!In.ArgVT.isScalarInteger()) {
        report_fatal_error("Only integer argument types are supported", false);
    }

    unsigned Reg = addLiveIn(DAG.getMachineFunction(), Favor::A0 + i, getRegClassFor(In.VT));
    SDValue InVal = DAG.getCopyFromReg(Chain, dl, Reg, In.VT);
    Glue = Chain.getValue(1);
    InVals.push_back(InVal);
    //ArgOps.push_back(DAG.getRegister(Favor::A0 + i, In.VT));
  }
  //ArgOps[0] = Chain;
 // ArgOps.push_back(Glue);

  // TODO: Need glue?
  return Chain;
}

const char *FavorTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case FavorISD::Ret:
    return "FavorISD::Ret";
  case FavorISD::CALL: return "FavorISD::CALL";
  default:
    return "Unknown FavorISD::Node";
  }
}