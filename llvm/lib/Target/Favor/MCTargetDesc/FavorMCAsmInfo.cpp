#include "FavorMCAsmInfo.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

void FavorMCAsmInfo::anchor() {}

FavorMCAsmInfo::FavorMCAsmInfo(const Triple& TT) {
  IsLittleEndian = true;
  AlignmentIsInBytes = true;
}