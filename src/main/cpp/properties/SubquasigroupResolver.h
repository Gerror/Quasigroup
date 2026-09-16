#ifndef QUASIGROUP_SUBQUASIGROUPRESOLVER_H
#define QUASIGROUP_SUBQUASIGROUPRESOLVER_H
#include "Quasigroup.h"

namespace Quasigroup {

class SubquasigroupResolver {
  static int nextStep(const Quasigroup *q, unsigned int *step, int border);
  static int checkStep(const Quasigroup *q, const unsigned int *step,
                       int border, unsigned int *a_sq, unsigned int *a_sqi,
                       unsigned int *a_q);

 public:
  static bool containsProperSubquasigroup(const Quasigroup *q);
  static int findSubquasigroup(const Quasigroup *q, int border,
                               unsigned int **a_sq);
};

}  // namespace Quasigroup

#endif  // QUASIGROUP_SUBQUASIGROUPRESOLVER_H
