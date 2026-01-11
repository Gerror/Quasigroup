#ifndef QUASIGROUP_SHIFTREGISTER_H
#define QUASIGROUP_SHIFTREGISTER_H

#include "FunctionFamily.h"
#include "generator/GeneratedObject.h"

namespace Quasigroup {
class ShiftRegister final : public FunctionFamily, public GeneratedObject {
 public:
  ShiftRegister(int k, int n, unsigned long long int seed = 0);

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_SHIFTREGISTER_H