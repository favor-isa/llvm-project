#include "Favor.h"
#include "FavorSubtarget.h"
#include "TargetInfo/FavorTargetInfo.h"
#include "FavorTargetMachine.h"
#include "MCTargetDesc/FavorMCInstPrinter.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/TargetRegistry.h"

#define DEBUG_TYPE "favor-asm-printer"

using namespace llvm;

namespace {
class FavorAsmPrinter : public AsmPrinter {
public:
  FavorAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
  : AsmPrinter(TM, std::move(Streamer)) {}

  StringRef getPassName() const override {
    return "Favor Assembly Printer";
  }

  void emitInstruction(const MachineInstr *MI) override;

  // Lower the MachineInstr to MCInst
  void lowerInstruction(const MachineInstr &MI, MCInst &Inst);

  // bool lowerPseudoInstExpansion(const MachineInstr *MI, MCInst &Inst);
private:

  MCOperand lowerSymbolOperand(const MachineOperand &MO, MCSymbol *Sym);
};

MCOperand FavorAsmPrinter::lowerSymbolOperand(const MachineOperand &MO, MCSymbol *Sym) {
  auto &Ctx = OutContext;
  const MCExpr *Expr = MCSymbolRefExpr::create(Sym, Ctx);
  assert(MO.isMBB() && "Only basic block symbols are supported");
  return MCOperand::createExpr(Expr);
}


void FavorAsmPrinter::lowerInstruction(const MachineInstr &MI, MCInst &Inst) {
  // This function should convert the MachineInstr to MCInst
  // The implementation will depend on the specific instruction set
  // and how you want to represent it in the MCInst format.
  // For now, we will just print the opcode and operands.

  Inst.setOpcode(MI.getOpcode());
  for (const auto &Op : MI.operands()) {
    MCOperand MCOp;
    switch (Op.getType()) {
      case MachineOperand::MO_Register:
        MCOp = MCOperand::createReg(Op.getReg());
        break;
      case MachineOperand::MO_Immediate:
        MCOp = MCOperand::createImm(Op.getImm());
        break;
      case MachineOperand::MO_MachineBasicBlock:
        MCOp = lowerSymbolOperand(Op, Op.getMBB()->getSymbol());
        break;
      // Add other operand types as needed
      default:
        llvm_unreachable("Unsupported operand type");
    }
    Inst.addOperand(MCOp);
  }
}

} // end anonymous namespace

void FavorAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // Lower the instruction to MCInst
  MCInst Inst;
  lowerInstruction(*MI, Inst);
  EmitToStreamer(*OutStreamer, Inst);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeFavorAsmPrinter() {
  RegisterAsmPrinter<FavorAsmPrinter> X(getTheFavorTarget());
}