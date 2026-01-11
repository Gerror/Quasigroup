#ifndef QUASIGROUP_QUASIGROUPGENERATOR_H
#define QUASIGROUP_QUASIGROUPGENERATOR_H

#include <quasigroup/factory/QuasigroupFactory.h>

#include <functional>
#include <set>

namespace Quasigroup {
class QuasigroupGenerator {
  QuasigroupFactory *factory;

 public:
  explicit QuasigroupGenerator(QuasigroupFactory *factory);

  Quasigroup *generate() const;

  Quasigroup *generate(
      const std::function<bool(Quasigroup *)> &condition) const;

  std::vector<Quasigroup *> generateVector(int count) const;

  std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash,
                     Quasigroup::QuasigroupEqualHash>
  generateUnorderedSet(int count) const;

  std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash,
                     Quasigroup::QuasigroupEqualHash>
  generateUnorderedSet(
      int count, const std::function<bool(Quasigroup *)> &condition) const;

  std::set<Quasigroup *, Quasigroup::QuasigroupPointerComparator> generateSet(
      int count) const;

  std::set<Quasigroup *, Quasigroup::QuasigroupPointerComparator> generateSet(
      int count, const std::function<bool(Quasigroup *)> &condition) const;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_QUASIGROUPGENERATOR_H