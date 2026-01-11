#ifndef QUASIGROUP_AFFINEQUASIGROUPFACTORY_H
#define QUASIGROUP_AFFINEQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroup.h"
#include "LatinSquareQuasigroupFactory.h"

namespace Quasigroup {
class AffineQuasigroupFactory final : public LatinSquareQuasigroupFactory {
 public:
  explicit AffineQuasigroupFactory(const int order)
      : LatinSquareQuasigroupFactory(order) {}

  LatinSquareQuasigroup *create() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_AFFINEQUASIGROUPFACTORY_H