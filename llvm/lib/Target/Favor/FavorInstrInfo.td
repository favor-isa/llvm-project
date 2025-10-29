include "FavorInstrFormats.td"

def FavorRetSDN : SDNode<"FavorISD::Ret",
    SDTNone,
    [SDNPHasChain, SDNPVariadic, SDNPOptInGlue]>;

def PsuedoRet : PsuedoFavorInst<(outs), (ins), "ret"> {
    let isReturn = 1;
    let isTerminator = 1;
}

def PsuedoLi : PsuedoFavorInst<(outs GPR64:$rd), (ins i32imm:$imm), "li $rd, $imm">;

def ADD_I32 : FavorALU_rr<"add", ".s32">;
def SUB_I32 : FavorALU_rr<"sub", ".s32">;

def : Pat<(FavorRetSDN), (PsuedoRet)>;

def : Pat<(i32 imm:$imm), (PsuedoLi imm:$imm)>;

def : Pat<(i32 (add GPR64:$rs1, GPR64:$rs2)), (ADD_I32 GPR64:$rs1, GPR64:$rs2)>;

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