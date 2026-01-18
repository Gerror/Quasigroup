#ifndef QUASIGROUP_PROPERFAMILYPERMUTATIONTRANSFORMER_H
#define QUASIGROUP_PROPERFAMILYPERMUTATIONTRANSFORMER_H
#include "PFQuasigroup.h"

namespace Quasigroup {
class PFQuasigroupPermutationTransformer {
 public:
  PFQuasigroupPermutationTransformer() = delete;
  static PFQuasigroup* transform(const PFQuasigroup* original);
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_PROPERFAMILYPERMUTATIONTRANSFORMER_H
