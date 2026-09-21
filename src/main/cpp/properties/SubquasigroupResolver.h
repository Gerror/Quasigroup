#ifndef QUASIGROUP_SUBQUASIGROUPRESOLVER_H
#define QUASIGROUP_SUBQUASIGROUPRESOLVER_H
#include "Quasigroup.h"

namespace Quasigroup {

class SubquasigroupResolver {
  static int getNextSeed(const Quasigroup *q, unsigned int *seed, int border);
  static int checkSeed(const Quasigroup *q, const unsigned int *seed,
                       int border, unsigned int *a_sq, unsigned int *a_sqi);

 public:
  static bool containsProperSubquasigroup(const Quasigroup *q, int border);
  static bool containsAnyProperSubquasigroup(const Quasigroup *q);
  static bool containsNonTrivialProperSubquasigroup(const Quasigroup *q);
  static int findSubquasigroup(const Quasigroup *q, int border,
                               unsigned int **a_sq);
};

}  // namespace Quasigroup

#endif  // QUASIGROUP_SUBQUASIGROUPRESOLVER_H
