#ifndef QUASIGROUP_KEPKATRANSFORMER_H
#define QUASIGROUP_KEPKATRANSFORMER_H

#include <quasigroup/Quasigroup.h>

namespace Quasigroup {
class KepkaTransformer {
 public:
  static Quasigroup *transform(const Quasigroup *original);
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_KEPKATRANSFORMER_H