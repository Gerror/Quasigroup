#ifndef QUASIGROUP_QUASIGROUPFACTORY_H
#define QUASIGROUP_QUASIGROUPFACTORY_H

#include <quasigroup/Quasigroup.h>

namespace Quasigroup {
class QuasigroupFactory {
 public:
  virtual ~QuasigroupFactory() = default;
  virtual int getOrder() = 0;

  virtual Quasigroup *create() = 0;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_QUASIGROUPFACTORY_H