#include "AbelianGroupFactory.h"

#include "AbelianGroup.h"

namespace Quasigroup {
Quasigroup *AbelianGroupFactory::create() { return new AbelianGroup(order); }
}  // namespace Quasigroup