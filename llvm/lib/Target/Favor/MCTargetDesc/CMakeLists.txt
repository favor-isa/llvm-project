add_llvm_component_library(LLVMFavorDesc
  FavorMCTargetDesc.cpp

  LINK_COMPONENTS
  CodeGenTypes
  MC
  FavorInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  Favor
  )