add_llvm_component_group(Favor)

set(LLVM_TARGET_DEFINITIONS Favor.td)

# tablegen(LLVM SparcGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM FavorGenAsmWriter.inc -gen-asm-writer)
# tablegen(LLVM SparcGenCallingConv.inc -gen-callingconv)
tablegen(LLVM FavorGenDAGISel.inc -gen-dag-isel)
# tablegen(LLVM SparcGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM FavorGenInstrInfo.inc -gen-instr-info)
# tablegen(LLVM SparcGenMCCodeEmitter.inc -gen-emitter)
# tablegen(LLVM SparcGenSDNodeInfo.inc -gen-sd-node-info -sdnode-namespace=SPISD)
# tablegen(LLVM SparcGenSearchableTables.inc -gen-searchable-tables)
tablegen(LLVM FavorGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM FavorGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(FavorCommonTableGen)

add_llvm_target(FavorCodeGen
  FavorAsmPrinter.cpp
  FavorInstrInfo.cpp
  FavorRegisterInfo.cpp
  FavorISelDAGToDAG.cpp
  FavorISelLowering.cpp
  FavorRegisterInfo.cpp
  FavorSubtarget.cpp
  FavorTargetObjectFile.cpp
  
  LINK_COMPONENTS
  MC
  TargetParser
  Target

  ADD_TO_COMPONENT
  Favor
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)