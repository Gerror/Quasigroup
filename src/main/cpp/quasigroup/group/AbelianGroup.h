#ifndef QUASIGROUP_ABELIANGROUP_H
#define QUASIGROUP_ABELIANGROUP_H

#include <quasigroup/Quasigroup.h>

#include "GeneratedObject.h"

namespace Quasigroup {
class AbelianGroup final : public Quasigroup, public GeneratedObject {
  std::vector<int> cyclicGroupsOrders;

 public:
  explicit AbelianGroup(int order, unsigned long long int seed = 0);

  // if abelian group = Z_n1 x Z_n2 x ... x Z_nm
  // then cyclicGroupsOrders is array of (n1, n2, ..., nm)
  explicit AbelianGroup(const std::vector<int> &cyclicGroupsOrders);

  [[nodiscard]] std::vector<int> getCyclicGroupsOrders() const;

  [[nodiscard]] std::vector<int> convertElementToGroupComponents(int element) const;

  [[nodiscard]] int convertGroupComponentsToElement(
      const std::vector<int> &groupComponents) const;

  [[nodiscard]] int getProduct(int x, int y) const override;

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_ABELIANGROUP_H