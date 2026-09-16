#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

#include <memory>
#include <random>
#include <unordered_set>

namespace Quasigroup {

struct UnorderedPair {
  int firstElement;
  int secondElement;
};

enum class AssociativityDeterminationStrategy {
  CompleteSearch,
  LightTest,
  BasisAssociativity  // This method works only for quasigroups known to be
                      // commutative.
};

class Quasigroup {
  int unit = -1;

  [[nodiscard]] std::string getRowsConcatenation() const;
  [[nodiscard]] bool isAssociativeByLightTest() const;
  [[nodiscard]] bool isAssociativeByCompleteSearch() const;
  [[nodiscard]] bool isAssociativeByBasis();

 public:
  class QuasigroupHash {
   public:
    size_t operator()(const Quasigroup *quasigroup) const;
  };

  class QuasigroupEqualHash {
   public:
    bool operator()(const Quasigroup *q1, const Quasigroup *q2) const;
  };

  struct QuasigroupPointerComparator {
    bool operator()(const Quasigroup *lhs, const Quasigroup *rhs) const {
      return *lhs < *rhs;
    }
  };

  virtual ~Quasigroup() = default;
  [[nodiscard]] virtual int getProduct(int x, int y) const = 0;
  [[nodiscard]] int getOrder() const;
  [[nodiscard]] bool isAffine(
      AssociativityDeterminationStrategy associativityStrategy =
          AssociativityDeterminationStrategy::LightTest) const;
  [[nodiscard]] bool isSimple() const;
  [[nodiscard]] bool isPolynomiallyComplete() const;
  [[nodiscard]] bool isAssociative(
      AssociativityDeterminationStrategy strategy =
          AssociativityDeterminationStrategy::LightTest);
  [[nodiscard]] bool isCommutative() const;
  [[nodiscard]] bool isIdempotent() const;
  [[nodiscard]] bool hasLeftUnit() const;
  [[nodiscard]] bool hasRightUnit() const;
  [[nodiscard]] bool hasUnit();
  [[nodiscard]] bool isShapeless() const;
  [[nodiscard]] bool oneOfShapelessIdentitiesIsSatisfied() const;
  [[nodiscard]] bool oneOfShapelessIdentitiesIsSatisfiedForK(int k) const;
  [[nodiscard]] bool isLoop();
  [[nodiscard]] bool isGroup();
  [[nodiscard]] bool isAbelianGroup();
  [[nodiscard]] bool containsProperSubquasigroup() const;
  [[nodiscard]] bool isQuadratical() const;
  [[nodiscard]] bool isHexagonal() const;
  [[nodiscard]] bool isGoldenSquare() const;
  [[nodiscard]] bool isRightModular() const;
  [[nodiscard]] bool isLeftModular() const;
  [[nodiscard]] bool isAffineRegularOctagonal() const;
  [[nodiscard]] bool isPentagonal() const;
  [[nodiscard]] int associativeTripletsCount() const;
  [[nodiscard]] int nonAssociativeTripletsCount() const;
  [[nodiscard]] int commutativePairsCount() const;
  [[nodiscard]] int nonCommutativePairsCount() const;
  [[nodiscard]] std::unordered_set<int> getGenerationSystem() const;
  int getUnit();

  friend std::ostream &operator<<(std::ostream &out, const Quasigroup &q);
  friend bool operator==(const Quasigroup &left, const Quasigroup &right);
  friend bool operator!=(const Quasigroup &left, const Quasigroup &right);
  friend bool operator<(const Quasigroup &left, const Quasigroup &right);
  friend bool operator<=(const Quasigroup &left, const Quasigroup &right);
  friend bool operator>(const Quasigroup &left, const Quasigroup &right);
  friend bool operator>=(const Quasigroup &left, const Quasigroup &right);

 protected:
  int order{};
  Quasigroup() = default;
};

}  // namespace Quasigroup

#endif