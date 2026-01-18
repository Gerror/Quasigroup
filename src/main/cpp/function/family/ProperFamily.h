#ifndef QUASIGROUP_PROPERFAMILY_H
#define QUASIGROUP_PROPERFAMILY_H

#define STEP_COUNT order* order

#include "FunctionFamily.h"
#include "generator/GeneratedObject.h"

namespace Quasigroup {
/*
 * Correct families of functions.
 * Used to generate quasigroups.
 */

class ProperFamily final : public FunctionFamily, public GeneratedObject {
  int order;

 public:
  int getOrder() const;

  ProperFamily(int k, int n, unsigned long long int seed = 0);

  ProperFamily(int k, int n, int** functionFamily);

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_PROPERFAMILY_H