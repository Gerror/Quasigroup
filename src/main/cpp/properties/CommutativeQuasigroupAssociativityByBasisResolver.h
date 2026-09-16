#ifndef QUASIGROUP_ASSOCIATIVITYBYBASISRESOLVER_H
#define QUASIGROUP_ASSOCIATIVITYBYBASISRESOLVER_H
#include <functional>

#include "Quasigroup.h"

namespace Quasigroup {
class CommutativeQuasigroupAssociativityByBasisResolver {
  static int findLocalUnit(int n, const std::function<int(int, int)> &op);
  static bool checkAssociativityOnBasis(const Quasigroup *q,
                                        const std::unordered_set<int> &S);
  static std::optional<std::unordered_set<int>> findBasis(Quasigroup *q);
  static std::unordered_set<int> findLargeSubgroup(
      int suborder, const std::function<int(int, int)> &operation);
  static std::pair<std::unordered_set<int>, std::unordered_set<int>>
  groupDecomposition(int n, double ell, const std::function<int(int, int)> &op);
  static bool isSubgroup(const std::unordered_set<int> &H,
                         const std::function<int(int, int)> &op);

 public:
  static bool isAssociative(Quasigroup *q);
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_ASSOCIATIVITYBYBASISRESOLVER_H
