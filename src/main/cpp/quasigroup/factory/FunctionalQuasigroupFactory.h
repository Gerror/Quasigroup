#ifndef QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H
#define QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H

#include "QuasigroupFactory.h"

namespace Quasigroup {
class FunctionalQuasigroupFactory : public QuasigroupFactory {
 protected:
  int k;
  int n;

 public:
  FunctionalQuasigroupFactory(const int k, const int n) : k(k), n(n) {};
  int getOrder() override { return pow(k, n); }
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_FUNCTIONALQUASIGROUPFACTORY_H