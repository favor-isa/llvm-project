include "FavorInstrFormats.td"

def FavorRetSDN : SDNode<"FavorISD::Ret",
    SDTNone,
    [SDNPHasChain, SDNPVariadic, SDNPOptInGlue]>;

def PsuedoRet : PsuedoFavorInst<(outs), (ins), "ret"> {
    let isReturn = 1;
    let isTerminator = 1;
}

def : Pat<(FavorRetSDN), (PsuedoRet)>;

def callseq_end : SDNode<"ISD::CALLSEQ_END", SDTNone,
    [SDNPHasChain, SDNPOptInGlue]>;

def ADJCALLSTACKDOWN : Instruction {
  let OutOperandList = (outs);
  let Namespace = "Favor";
  let InOperandList = (ins);
  let AsmString = "sub sp";
  let Pattern = [(callseq_end)];
}

def ADJCALLSTACKUP : Instruction {
  let OutOperandList = (outs);
  let Namespace = "Favor";
  let InOperandList = (ins);
  let AsmString = "add sp";
  let Pattern = [(callseq_end)];
}