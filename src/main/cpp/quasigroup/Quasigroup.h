#ifndef QUASIGROUP_QUASIGROUP_H
#define QUASIGROUP_QUASIGROUP_H

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

/*
 * Abstract class of finite 2-quasigroups
 */

class Quasigroup {
  // Two functions needed to find subquasigroups
  int nextStep(unsigned int *step, int border) const;

  int checkStep(const unsigned int *step, int border, unsigned int *a_sq,
                unsigned int *a_sqi, unsigned int *a_q) const;

  [[nodiscard]] std::string getRowsConcatenation() const;

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

  [[nodiscard]] bool isAffine(bool useLightTest = true) const;

  [[nodiscard]] bool isSimple() const;

  [[nodiscard]] bool isPolynomiallyComplete() const;

  // deprecated, use isAssociativeByLightTest
  [[nodiscard]] bool isAssociative() const;

  [[nodiscard]] bool isAssociativeByLightTest() const;

  [[nodiscard]] bool isCommutative() const;

  [[nodiscard]] bool isIdempotent() const;

  [[nodiscard]] bool hasLeftUnit() const;

  [[nodiscard]] bool hasRightUnit() const;

  [[nodiscard]] bool hasUnit() const;

  [[nodiscard]] bool isShapeless() const;

  [[nodiscard]] bool shapelessIdentitiesIsSatisfied() const;

  [[nodiscard]] bool shapelessIdentitiesIsSatisfied(int k) const;

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