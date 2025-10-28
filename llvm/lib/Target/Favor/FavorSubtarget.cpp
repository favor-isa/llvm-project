#include "Favor.h"
#include "FavorSubtarget.h"
#include "FavorRegisterInfo.h"
#include "FavorTargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "favor-subtarget"

#define GET_SUBTARGETINFO_CTOR
#define GET_SUBTARGETINFO_TARGET_DESC
#include "FavorGenSubtargetInfo.inc"