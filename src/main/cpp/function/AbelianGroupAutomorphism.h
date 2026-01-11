#ifndef QUASIGROUP_ABELIANGROUPAUTOMORPHISM_H
#define QUASIGROUP_ABELIANGROUPAUTOMORPHISM_H

#include "AbelianGroup.h"
#include "GeneratedObject.h"

namespace Quasigroup {
class AbelianGroupAutomorphism final : public GeneratedObject {
  AbelianGroup *group;
  std::vector<int> images;

 public:
  explicit AbelianGroupAutomorphism(AbelianGroup *group,
                                    unsigned long long int seed = 0);

  int getImage(int x) const;

  bool isCorrectHomomorphism() const;

  friend std::ostream &operator<<(std::ostream &out,
                                  const AbelianGroupAutomorphism &a);

 protected:
  void generate() override;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_ABELIANGROUPAUTOMORPHISM_H