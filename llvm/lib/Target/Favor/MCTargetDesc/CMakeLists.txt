add_llvm_component_library(LLVMFavorDesc
  FavorMCAsmInfo.cpp
  FavorMCTargetDesc.cpp
  FavorMCInstPrinter.cpp

  LINK_COMPONENTS
  CodeGenTypes
  MC
  FavorInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  Favor
  )