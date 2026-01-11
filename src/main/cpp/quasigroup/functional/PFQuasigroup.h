#ifndef QUASIGROUP_PFQUASIGROUP_H
#define QUASIGROUP_PFQUASIGROUP_H

#include "FunctionalQuasigroup.h"
#include "function/family/ProperFamily.h"
#include "generator/GeneratedObject.h"

namespace Quasigroup {
/*
 * Quasigroups based on proper families of functions
 */

class PFQuasigroup final : public FunctionalQuasigroup, public GeneratedObject {
  int *piValue;

 public:
  int getProduct(int x, int y) const override;

  explicit PFQuasigroup(const ProperFamily &properFamily,
                        unsigned long long int seed = 0);

  PFQuasigroup(int k, int n, unsigned long long int seed = 0);

  ~PFQuasigroup() override;

  friend bool operator==(const PFQuasigroup &q1, const PFQuasigroup &q2);

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_PFQUASIGROUP_H