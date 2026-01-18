#ifndef QUASIGROUP_PFPERMUTATEDQUASIGROUP_H
#define QUASIGROUP_PFPERMUTATEDQUASIGROUP_H
#include "PFQuasigroup.h"

namespace Quasigroup {
class PFPermutatedQuasigroup final : public PFQuasigroup {
  std::vector<int> xPermutation;
  std::vector<int> yPermutation;
  std::vector<int> functionPermutation;

 public:
  PFPermutatedQuasigroup(const PFQuasigroup &original,
                         const std::vector<int> &xPermutation,
                         const std::vector<int> &yPermutation,
                         const std::vector<int> &functionPermutation);

  int getProduct(int x, int y) const override;
};
}  // namespace Quasigroup
#endif  // QUASIGROUP_PFPERMUTATEDQUASIGROUP_H
