add_llvm_component_library(LLVMFavorInfo
  FavorTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  Favor
  )