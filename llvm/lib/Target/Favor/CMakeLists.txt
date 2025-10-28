add_llvm_component_group(Favor)

set(LLVM_TARGET_DEFINITIONS Favor.td)

# tablegen(LLVM SparcGenAsmMatcher.inc -gen-asm-matcher)
# tablegen(LLVM SparcGenAsmWriter.inc -gen-asm-writer)
# tablegen(LLVM SparcGenCallingConv.inc -gen-callingconv)
# tablegen(LLVM SparcGenDAGISel.inc -gen-dag-isel)
# tablegen(LLVM SparcGenDisassemblerTables.inc -gen-disassembler)
# tablegen(LLVM SparcGenInstrInfo.inc -gen-instr-info)
# tablegen(LLVM SparcGenMCCodeEmitter.inc -gen-emitter)
# tablegen(LLVM SparcGenRegisterInfo.inc -gen-register-info)
# tablegen(LLVM SparcGenSDNodeInfo.inc -gen-sd-node-info -sdnode-namespace=SPISD)
# tablegen(LLVM SparcGenSearchableTables.inc -gen-searchable-tables)
# tablegen(LLVM SparcGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM FavorGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(FavorCommonTableGen)

add_llvm_target(FavorCodeGen
  FavorRegisterInfo.cpp

  LINK_COMPONENTS
  MC
  TargetParser
  Target

  ADD_TO_COMPONENT
  Favor
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)