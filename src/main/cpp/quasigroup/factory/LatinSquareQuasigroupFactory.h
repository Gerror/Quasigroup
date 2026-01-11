#ifndef QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H
#define QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H

#include "LatinSquareQuasigroup.h"
#include "QuasigroupFactory.h"

namespace Quasigroup {
class LatinSquareQuasigroupFactory : public QuasigroupFactory {
 protected:
  int order;

 public:
  explicit LatinSquareQuasigroupFactory(const int order) : order{order} {}

  LatinSquareQuasigroup *create() override = 0;

  int getOrder() override { return order; };
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_LATINSQUAREQUASIGROUPFACTORY_H