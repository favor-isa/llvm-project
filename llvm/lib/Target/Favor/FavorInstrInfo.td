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

def SDT_FavorFrameIndex : SDTypeProfile<1, 1, [SDTCisVT<0, i64>]>;
def frame_index : SDNode<"FavorISD::FRAME_INDEX", SDT_FavorFrameIndex,
  [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue,
  SDNPVariadic]>;

def PsuedoRet : PsuedoFavorInst<(outs), (ins), "ret"> {
    let isReturn = 1;
    let isTerminator = 1;
}

def FI : Operand<i64> {
  //let PrintMethod = "printFrameIndexOperand";
}

def PsuedoLi : PsuedoFavorInst<(outs GPR64:$rd), (ins i32imm:$imm), "li.u32 $rd, $imm">;
def LI_U64 : PsuedoFavorInst<(outs GPR64:$rd), (ins i64imm:$imm), "li.u64 $rd, $imm">;
def PsuedoLiR32 : PsuedoFavorInst<(outs GPR64:$rd), (ins i64imm:$addr), "li.r32 $rd, $addr">;

// Two's complement: Addition & subtraction use unsigned ops
def ADD_I32 : FavorALU_rr<"add", ".u32">;
def SUB_I32 : FavorALU_rr<"sub", ".u32">;

//def ADDI_I32 : FavorALU_ri<"addi", ".u32">;
def ADDI_I32: FavorInst<(outs GPR64:$rd), (ins GPR64:$rs, i32imm:$val), "addi.u32 $rd, $val"> {
  let Constraints = "$rd = $rs";
}

def LOAD_I32 : FavorInst<(outs GPR64:$rd), (ins GPR64:$addr), "ld.u32 $rd, [$addr]">;
def STORE_I32 : FavorInst<(outs), (ins GPR64:$dst, GPR64:$addr), "st.u32 $dst, [$addr]">;

def STORE_I32_F : FavorInst<(outs), (ins GPR64:$dst, i64imm:$offset), "st.u32 $dst, [sp + $offset]">;

// JANK idea: Try to synthesize i64 = FrameIndex<> with this
def SP_JANK : FavorInst<(outs GPR64:$rd), (ins i64imm:$offset), "add.u64 $rd, $rd, sp\naddi.u64 $rd, $offset">;

def LOAD_SP_I32 : FavorInst<(outs GPR64:$rd), (ins i64imm:$offset), "ld.u32 $rd, [sp + $offset]">;
def STORE_SP_I32 : FavorInst<(outs), (ins GPR64:$dst, i64imm:$offset), "st.u32 $dst, [sp + $offset]">;

def CALL : FavorInst<(outs), (ins i64imm:$disp, variable_ops), "j.l $disp">;

def : Pat<(FavorRetSDN), (PsuedoRet)>;

def : Pat<(i32 imm:$imm), (PsuedoLi imm:$imm)>;
def : Pat<(i64 imm:$imm), (LI_U64 imm:$imm)>;

def : Pat<(i64 texternalsym:$dst), (PsuedoLiR32 texternalsym:$dst)>;
def : Pat<(i64 tglobaladdr:$dst), (PsuedoLiR32 tglobaladdr:$dst)>;

def : Pat<(i32 (add GPR64:$rs1, GPR64:$rs2)), (ADD_I32 GPR64:$rs1, GPR64:$rs2)>;
def : Pat<(i32 (add GPR64:$rs1, imm:$is2)), (ADDI_I32 GPR64:$rs1, imm:$is2)>;

// Thoughts:
// To get something like loads/stores to the stack to work, we can't just
// match on i64:$addr like this, because it means LLVM synthesizes code to
// convert frameindex into an i64, which causes all sorts of issues (?)
//
// So we probably want some sort of load/store that is either handled in
// DAGtoDAG, or in Lowering...
def : Pat<(i32 (load i64:$addr)), (LOAD_I32 GPR64:$addr)>;
def : Pat<(store i32:$value, i64:$addr), (STORE_I32 GPR64:$value, GPR64:$addr)>;

// def : Pat<(i32 (frame_index i64imm:$offset)), (LOAD_SP_I32 i64imm:$offset)>;

//def : Pat<(store i32:$value, (frameindex i64imm:$offset)), (STORE_I32_F GPR64:$value, i64imm:$offset)>;
def : Pat<(i32 (load (frameindex:$fi))), (LOAD_SP_I32 imm:$fi)>;
def : Pat<(store i32:$value, (frameindex:$fi)), (STORE_SP_I32 GPR64:$value, imm:$fi)>;

//def : Pat<(i64 (frameindex:$fi)), (SP_JANK imm:$fi)>;

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