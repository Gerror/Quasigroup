#ifndef QUASIGROUP_SRQUASIGROUP_H
#define QUASIGROUP_SRQUASIGROUP_H

#include "FunctionalQuasigroup.h"
#include "function/family/ShiftRegister.h"

namespace Quasigroup {
/*
 * Quasigroups based on feedback shift registers
 */

class SRQuasigroup final : public FunctionalQuasigroup, GeneratedObject {
  std::vector<int> c;
  bool inverseOperations;

 public:
  int getProduct(int x, int y) const override;

  explicit SRQuasigroup(const ShiftRegister &shiftRegister,
                        bool inverseOperations = false);

  SRQuasigroup(int k, int n, bool inverseOperations = false,
               unsigned long long int seed = 0);

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_SRQUASIGROUP_H