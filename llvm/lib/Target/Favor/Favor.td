include "llvm/Target/Target.td"
include "FavorRegisterInfo.td"

// def FavorAsmWriter : AsmWriter {
//  int PassSubtarget = 1;
// }

def : ProcessorModel<"generic", NoSchedModel, []>;

def Favor : Target {
  // let InstructionSet = FavorInstrInfo;
  // let AssemblyWriters = [FavorAsmWriter];
  // let AssemblyParsers = [];
  // let AssemblyParserVariants = [];
  // let AllowRegisterRenaming = 1;
}
