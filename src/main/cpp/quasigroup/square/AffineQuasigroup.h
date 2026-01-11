#ifndef QUASIGROUP_AFFINEQUASIGROUP_H
#define QUASIGROUP_AFFINEQUASIGROUP_H

#include <function/AbelianGroupAutomorphism.h>

#include "LatinSquareQuasigroup.h"
#include "generator/GeneratedObject.h"

namespace Quasigroup {
class AffineQuasigroup final : public LatinSquareQuasigroup,
                               public GeneratedObject {
  AbelianGroup *abelianGroup;
  AbelianGroupAutomorphism *alpha;
  AbelianGroupAutomorphism *beta;
  int c;

 public:
  explicit AffineQuasigroup(int order, unsigned long long int seed = 0);

  ~AffineQuasigroup() override;

  AbelianGroup *getAbelianGroup() const;

  AbelianGroupAutomorphism *getAlpha() const;

  AbelianGroupAutomorphism *getBeta() const;

  int getC() const;

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_AFFINEQUASIGROUP_H