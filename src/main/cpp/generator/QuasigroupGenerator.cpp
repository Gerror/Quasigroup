#include "QuasigroupGenerator.h"

#include "LatinSquareQuasigroup.h"

namespace Quasigroup {
QuasigroupGenerator::QuasigroupGenerator(QuasigroupFactory *factory) {
  this->factory = factory;
}

Quasigroup *QuasigroupGenerator::generate() const { return factory->create(); }

Quasigroup *QuasigroupGenerator::generate(
    const std::function<bool(Quasigroup *)> &condition) const {
  while (true) {
    const auto q = factory->create();
    if (condition(q)) {
      return q;
    }
    delete q;
  }
}

std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash,
                   Quasigroup::QuasigroupEqualHash>
QuasigroupGenerator::generateUnorderedSet(const int count) const {
  return generateUnorderedSet(count, [](Quasigroup *q) { return true; });
}

std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash,
                   Quasigroup::QuasigroupEqualHash>
QuasigroupGenerator::generateUnorderedSet(
    const int count, const std::function<bool(Quasigroup *)> &condition) const {
  std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash,
                     Quasigroup::QuasigroupEqualHash>
      result;

  while (result.size() != count) {
    auto q = generate(condition);

    const int sizeBefore = result.size();
    result.insert(q);

    if (const int sizeAfter = result.size(); sizeAfter == sizeBefore) {
      delete q;
    }
  }

  return result;
}

std::set<Quasigroup *, Quasigroup::QuasigroupPointerComparator>
QuasigroupGenerator::generateSet(const int count) const {
  return generateSet(count, [](Quasigroup *) { return true; });
}

std::set<Quasigroup *, Quasigroup::QuasigroupPointerComparator>
QuasigroupGenerator::generateSet(
    const int count, const std::function<bool(Quasigroup *)> &condition) const {
  std::set<Quasigroup *, Quasigroup::QuasigroupPointerComparator> result;

  while (result.size() != count) {
    auto q = generate(condition);

    const int sizeBefore = result.size();
    result.insert(q);

    if (const int sizeAfter = result.size(); sizeAfter == sizeBefore) {
      delete q;
    }
  }

  return result;
}

std::vector<Quasigroup *> QuasigroupGenerator::generateVector(
    const int count) const {
  std::vector<Quasigroup *> result(count);
  for (int i = 0; i < count; ++i) {
    result[i] = generate();
  }

  return result;
}
}  // namespace Quasigroup