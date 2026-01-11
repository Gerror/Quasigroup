#ifndef QUASIGROUP_DIHEDRALGROUP_H
#define QUASIGROUP_DIHEDRALGROUP_H

#include <quasigroup/square/LatinSquareQuasigroup.h>

namespace Quasigroup {
class DihedralGroup final : public LatinSquareQuasigroup {
 public:
  explicit DihedralGroup(int order);
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_DIHEDRALGROUP_H