#ifndef LLVM_LIB_TARGET_FAVOR_MCTARGETDESC_H
#define LLVM_LIB_TARGET_FAVOR_MCTARGETDESC_H

#define GET_REGINFO_ENUM
#include "FavorGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "FavorGenSubtargetInfo.inc"

#define GET_INSTRINFO_ENUM
#include "FavorGenInstrInfo.inc"

#endif