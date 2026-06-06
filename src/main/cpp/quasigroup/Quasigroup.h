#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

#include <functional>
#include <memory>
#include <random>
#include <unordered_set>

namespace Quasigroup {
/*
 * Unordered pairs needed for simplicity test
 */

struct UnorderedPair {
  int firstElement;
  int secondElement;
};

enum class AssociativityDeterminationStrategy {
  CompleteSearch,
  LightTest,
  Basis4Associativity  // for affinity algorithm only!
};

/*
 * Abstract class of finite 2-quasigroups
 */

class Quasigroup {
  // Two functions needed to find subquasigroups
  int nextStep(unsigned int *step, int border) const;

  int checkStep(const unsigned int *step, int border, unsigned int *a_sq,
                unsigned int *a_sqi, unsigned int *a_q) const;

  [[nodiscard]] std::string getRowsConcatenation() const;

  [[nodiscard]] bool isAssociativeByLightTest() const;
  [[nodiscard]] bool isAssociativeByCompleteSearch() const;
  [[nodiscard]] bool isAssociativeByBasis4Associativity() const;

  // for Basis4Associativity only!
  [[nodiscard]] bool check4Associativity(
      const std::unordered_set<int> &S) const;
  [[nodiscard]] std::unordered_set<int> findBasis() const;
  [[nodiscard]] std::pair<std::unordered_set<int>, std::unordered_set<int>>
  groupDecomposition(int suborder, double ell,
                     const std::vector<int> &elemToGlobal,
                     const std::function<int(int, int)> &operation) const;
  [[nodiscard]] std::unordered_set<int> findLargeSubgroup(
      int suborder, const std::function<int(int, int)> &operation) const;
  [[nodiscard]] std::unordered_set<int> leftTransversal(
      int suborder, const std::unordered_set<int> &H,
      const std::function<int(int, int)> &operation) const;
  [[nodiscard]] std::unordered_set<int> rightTransversal(
      int suborder, const std::unordered_set<int> &H,
      const std::function<int(int, int)> &operation) const;

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
          AssociativityDeterminationStrategy::LightTest) const;

  [[nodiscard]] bool isCommutative() const;

  [[nodiscard]] bool isIdempotent() const;

  [[nodiscard]] bool hasLeftUnit() const;

  [[nodiscard]] bool hasRightUnit() const;

  [[nodiscard]] bool hasUnit() const;

  [[nodiscard]] bool isShapeless() const;

  [[nodiscard]] bool oneOfShapelessIdentitiesIsSatisfied() const;

  [[nodiscard]] bool oneOfShapelessIdentitiesIsSatisfiedForK(int k) const;

  [[nodiscard]] bool isLoop() const;

  [[nodiscard]] bool isGroup() const;

  [[nodiscard]] bool isAbelianGroup() const;

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

  int findSubquasigroup(int border, unsigned int **a_sq) const;

  std::unordered_set<int> getGenerationSystem() const;

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

#endif  // QUASIGROUP_QUASIGROUP_H