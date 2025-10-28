class FavorInst<dag outs, dag ins, string asmString> : Instruction {
    let Namespace = "Favor";
    let OutOperandList = outs;
    let InOperandList = ins;
    let AsmString = asmString;
}

class PsuedoFavorInst<dag outs, dag ins, string asmString> : FavorInst<outs, ins, asmString>  {
    let isPseudo = 1;
    let isCodeGenOnly = 1;
}

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
    class FavorALU_rr<string opcode, string ty> : FavorInst<(outs GPR64:$rd), (ins GPR64:$rs1, GPR64:$rs2),
        !strconcat(opcode, ty, " $rd, $rs1, $rs2")>;