#ifndef LLVM_LIB_TARGET_FAVOR_FAVORTARGETINFO_H
#define LLVM_LIB_TARGET_FAVOR_FAVORTARGETINFO_H

namespace llvm {
class Target;

Target &getTheFavorTarget();
}

#endif