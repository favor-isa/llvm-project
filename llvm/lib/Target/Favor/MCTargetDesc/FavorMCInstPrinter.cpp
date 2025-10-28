#include "FavorMCInstPrinter.h"
#include "FavorInstrInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCAsmInfo.h"
#define DEBUG_TYPE "favor-mcinst-printer"

using namespace llvm;

#define PRINT_ALIAS_INSTR
#include "FavorGenAsmWriter.inc"

void FavorInstPrinter::printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
  const MCSubtargetInfo &STI, raw_ostream &O) {
    // check if we have an alias
    if (!printAliasInstr(MI, Address, O)) {
      printInstruction(MI, Address, O);
    }
    printAnnotation(O, Annot);
}

void FavorInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) {
    OS << StringRef(getRegisterName(Reg)).lower();
}

void FavorInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                   raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg()) {
    printRegName(O, Op.getReg());
    return;
  }

  if (Op.isImm()) {
    O << Op.getImm();
    return;
  }

  assert(Op.isExpr() && "unknown operand type");
  MAI.printExpr(O, *Op.getExpr());
}