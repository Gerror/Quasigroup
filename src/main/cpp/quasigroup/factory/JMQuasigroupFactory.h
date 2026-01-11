#ifndef QUASIGROUP_JMQUASIGROUPFACTORY_H
#define QUASIGROUP_JMQUASIGROUPFACTORY_H

#include "JMQuasigroup.h"
#include "LatinSquareQuasigroupFactory.h"

namespace Quasigroup {
class JMQuasigroupFactory final : public LatinSquareQuasigroupFactory {
 public:
  explicit JMQuasigroupFactory(const int order)
      : LatinSquareQuasigroupFactory(order) {};

  JMQuasigroup *create() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_JMQUASIGROUPFACTORY_H