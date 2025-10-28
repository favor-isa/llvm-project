#ifndef LLVM_LIB_TARGET_FAVOR_MCTARGETDESC_FAVORMCASMINFO_H
#define LLVM_LIB_TARGET_FAVOR_MCTARGETDESC_FAVORMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;
class FavorMCAsmInfo final : public MCAsmInfoELF {
  void anchor() override;
public:
  explicit FavorMCAsmInfo(const Triple &TheTriple);
};
} // end namespace llvm

#endif