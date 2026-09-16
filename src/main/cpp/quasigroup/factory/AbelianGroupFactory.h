#ifndef QUASIGROUP_ABELIANGROUPFACTORY_H
#define QUASIGROUP_ABELIANROUPFACTORY_H

#include "LatinSquareQuasigroupFactory.h"

namespace Quasigroup {
class AbelianGroupFactory final : public QuasigroupFactory {
 protected:
  int order;

 public:
  explicit AbelianGroupFactory(const int order) : order(order) {}

  Quasigroup *create() override;

  int getOrder() override { return order; }
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_ABELIANGROUPFACTORY_H