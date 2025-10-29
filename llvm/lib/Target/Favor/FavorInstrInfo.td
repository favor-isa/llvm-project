include "FavorInstrFormats.td"

def calltarget : Operand<i64> {
  let OperandType = "OPERAND_PCREL";
}

def FavorRetSDN : SDNode<"FavorISD::Ret",
    SDTNone,
    [SDNPHasChain, SDNPVariadic, SDNPOptInGlue]>;

def SDT_FavorCall : SDTypeProfile<0, -1, [SDTCisVT<0, i64>]>;
def call : SDNode<"FavorISD::CALL", SDT_FavorCall,
  [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue,
  SDNPVariadic]>;

def PsuedoRet : PsuedoFavorInst<(outs), (ins), "ret"> {
    let isReturn = 1;
    let isTerminator = 1;
}

def PsuedoLi : PsuedoFavorInst<(outs GPR64:$rd), (ins i32imm:$imm), "li.u32 $rd, $imm">;
def PsuedoLiR32 : PsuedoFavorInst<(outs GPR64:$rd), (ins i64imm:$addr), "li.r32 $rd, $addr">;

// Two's complement: Addition & subtraction use unsigned ops
def ADD_I32 : FavorALU_rr<"add", ".u32">;
def SUB_I32 : FavorALU_rr<"sub", ".u32">;

def CALL : FavorInst<(outs), (ins i64imm:$disp, variable_ops), "j.l $disp">;

def : Pat<(FavorRetSDN), (PsuedoRet)>;

def : Pat<(i32 imm:$imm), (PsuedoLi imm:$imm)>;
def : Pat<(i64 texternalsym:$dst), (PsuedoLiR32 texternalsym:$dst)>;

def : Pat<(i32 (add GPR64:$rs1, GPR64:$rs2)), (ADD_I32 GPR64:$rs1, GPR64:$rs2)>;

def : Pat<(call tglobaladdr:$dst),
          (CALL tglobaladdr:$dst)>;
def : Pat<(call texternalsym:$dst),
          (CALL texternalsym:$dst)>;

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