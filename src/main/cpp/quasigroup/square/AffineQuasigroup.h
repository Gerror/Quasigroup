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

  void initializeLatinSquare() const;

 public:
  explicit AffineQuasigroup(int order, unsigned long long int seed = 0);

  explicit AffineQuasigroup(AbelianGroup *abelian_group,
                            AbelianGroupAutomorphism *alpha,
                            AbelianGroupAutomorphism *beta, int c);

  ~AffineQuasigroup() override;

  [[nodiscard]] AbelianGroup *getAbelianGroup() const;

  [[nodiscard]] AbelianGroupAutomorphism *getAlpha() const;

  [[nodiscard]] AbelianGroupAutomorphism *getBeta() const;

  [[nodiscard]] int getC() const;

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_AFFINEQUASIGROUP_H