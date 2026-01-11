#ifndef QUASIGROUP_ALTERNATINGGROUP_H
#define QUASIGROUP_ALTERNATINGGROUP_H

#include <quasigroup/square/LatinSquareQuasigroup.h>

namespace Quasigroup {
class AlternatingGroup final : public LatinSquareQuasigroup {
 public:
  explicit AlternatingGroup(int degree);
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_ALTERNATINGGROUP_H