#include "AffineQuasigroupFactory.h"

#include "AffineQuasigroup.h"

namespace Quasigroup {
LatinSquareQuasigroup *AffineQuasigroupFactory::create() {
  return new AffineQuasigroup(order);
}
}  // namespace Quasigroup