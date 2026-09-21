#include "Quasigroup.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <ostream>
#include <queue>
#include <random>
#include <unordered_set>

#include "LatinSquareQuasigroup.h"
#include "properties/CommutativeQuasigroupAssociativityByBasisResolver.h"
#include "properties/SubquasigroupResolver.h"
#include "utils/Helper.h"
namespace Quasigroup {
bool Quasigroup::isIdempotent() const {
  for (int x = 0; x < order; x++) {
    if (getProduct(x, x) != x) {
      return false;
    }
  }

  return true;
}

bool Quasigroup::hasLeftUnit() const {
  for (int e = 0; e < order; e++) {
    auto count = 0;
    for (int y = 0; y < order; y++) {
      if (getProduct(e, y) != y) {
        break;
      }
      count++;
    }

    if (count == order) {
      return true;
    }
  }

  return false;
}

bool Quasigroup::hasRightUnit() const {
  for (int e = 0; e < order; e++) {
    auto count = 0;
    for (int y = 0; y < order; y++) {
      if (getProduct(y, e) != y) {
        break;
      }
      count++;
    }

    if (count == order) {
      return true;
    }
  }

  return false;
}

bool Quasigroup::isLoop() { return hasUnit(); }

bool Quasigroup::isGroup() { return isLoop() && isAssociativeByLightTest(); }

bool Quasigroup::isAbelianGroup() { return isGroup() && isCommutative(); }

bool Quasigroup::containsAnyProperSubquasigroup() const {
  return SubquasigroupResolver::containsAnyProperSubquasigroup(this);
}

bool Quasigroup::containsNonTrivialProperSubquasigroup() const {
  return SubquasigroupResolver::containsNonTrivialProperSubquasigroup(this);
}

bool Quasigroup::isShapeless(
    const AssociativityDeterminationStrategy strategy) {
  return !isIdempotent() && !isCommutative() && !isAssociative(strategy) &&
         !hasLeftUnit() && !hasRightUnit() &&
         !containsAnyProperSubquasigroup() &&
         !oneOfShapelessIdentitiesIsSatisfied();
}

bool Quasigroup::oneOfShapelessIdentitiesIsSatisfied() const {
  int leftK = 1;
  int rightK = 1;

  bool leftAlreadyNotSatisfied = false;
  bool rightAlreadyNotSatisfied = false;
  for (int x = 0; x < order; x++) {
    std::vector leftVisited(order, false);
    std::vector rightVisited(order, false);
    for (int y = 0; y < order; y++) {
      if (!leftAlreadyNotSatisfied && !leftVisited[y]) {
        auto leftProduct = y;
        auto leftCycleOrder = 1;
        for (int z = 0; z < order; z++) {
          leftVisited[leftProduct] = true;
          leftProduct = getProduct(x, leftProduct);
          if (leftProduct == y) break;

          leftCycleOrder++;
        }

        leftK = std::lcm(leftK, leftCycleOrder);
        if (leftK >= 2 * order) leftAlreadyNotSatisfied = true;
      }

      if (!rightAlreadyNotSatisfied && !rightVisited[y]) {
        auto rightProduct = y;
        auto rightCycleOrder = 1;
        for (int z = 0; z < order; z++) {
          rightVisited[rightProduct] = true;
          rightProduct = getProduct(rightProduct, x);

          if (rightProduct == y) break;

          rightCycleOrder++;
        }

        rightK = std::lcm(rightK, rightCycleOrder);
        if (rightK >= 2 * order) rightAlreadyNotSatisfied = true;
      }

      if (leftAlreadyNotSatisfied && rightAlreadyNotSatisfied) return false;
    }
  }

  return !leftAlreadyNotSatisfied || !rightAlreadyNotSatisfied;
}

bool Quasigroup::isAssociative(
    const AssociativityDeterminationStrategy strategy) {
  switch (strategy) {
    case AssociativityDeterminationStrategy::LightTest:
      return isAssociativeByLightTest();
    case AssociativityDeterminationStrategy::CompleteSearch:
      return isAssociativeByCompleteSearch();
    case AssociativityDeterminationStrategy::BasisAssociativity:
      return isAssociativeByBasis();
    default:
      return isAssociativeByLightTest();
  }
}

bool Quasigroup::isAssociativeByCompleteSearch() const {
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      for (int k = 0; k < order; k++) {
        if (getProduct(i, getProduct(j, k)) !=
            getProduct(getProduct(i, j), k)) {
          return false;
        }
      }
    }
  }

  return true;
}

/*
 * Light test to check associativity:
 * Find the generating set S and check the identities
 * (x * g) * y = x * (g * y) for all elements x, y from the quasigroup and
 * for all elements g of S.
 */
bool Quasigroup::isAssociativeByLightTest() const {
  std::unordered_set<int> S, R, T;
  for (int i = 0; i < order; i++) {
    T.insert(i);
  }

  while (!T.empty()) {
    int currentRSize;
    int newRSize;
    int begin = (*T.begin());

    S.insert(begin);
    R.insert(begin);
    T.erase(begin);

    do {
      currentRSize = R.size();
      for (auto const &element : R) {
        int lElement = getProduct(begin, element);
        int rElement = getProduct(element, begin);

        if (T.count(lElement) != 0) {
          T.erase(lElement);
          R.insert(lElement);
        }

        if (T.count(rElement) != 0) {
          T.erase(rElement);
          R.insert(rElement);
        }
      }
      newRSize = R.size();
    } while (currentRSize != newRSize);
  }

  for (int x = 0; x < order; x++) {
    for (auto const &g : S) {
      for (int y = 0; y < order; y++) {
        if (getProduct(getProduct(x, g), y) !=
            getProduct(x, getProduct(g, y))) {
          return false;
        }
      }
    }
  }

  return true;
}

bool Quasigroup::hasUnit() {
  if (unit != -1) return true;
  if (order <= 0) return false;

  int candidate = -1;

  for (int x = 0; x < order; ++x) {
    if (getProduct(0, x) == 0) {
      candidate = x;
      break;
    }
  }

  if (candidate == -1) return false;

  for (int x = 0; x < order; ++x) {
    if (getProduct(candidate, x) != x || getProduct(x, candidate) != x) {
      return false;
    }
  }

  unit = candidate;
  return true;
}

bool Quasigroup::isAssociativeByBasis() {
  return CommutativeQuasigroupAssociativityByBasisResolver::isAssociative(this);
}

bool Quasigroup::isCommutative() const {
  for (int x = 0; x < order; x++) {
    for (int y = x + 1; y < order; y++) {
      if (getProduct(x, y) != getProduct(y, x)) {
        return false;
      }
    }
  }

  return true;
}

bool Quasigroup::isAffine(
    const AssociativityDeterminationStrategy associativityStrategy) const {
  /*
   * latinSquare далее - матрица L, её i-я строка - s(i)
   *
   * (1)
   * По матрице L строим матрицу L' (tempQuasigroup), в которой при каждом i =
   * 1, ..., order строка с номером i содержит перестановку s(i) * (s(1))^-1
   */

  int reverseFirstLine[order];
  int alpha = 0, beta = 0;

  for (int i = 0; i < order; i++) {
    reverseFirstLine[getProduct(0, i)] = i;
  }

  auto productOfTempQuasigroup{[&](const int x, const int y) {
    return getProduct(x, reverseFirstLine[y]);
  }};
  const auto tempQuasigroup =
      std::make_unique<LatinSquareQuasigroup>(order, productOfTempQuasigroup);

  /*
   * (2)
   * По матрице L' (tempQuasigroup) строим матрицу L'', полученную из L'
   * перестановкой строк, строк, такой что первый столбец L'' совпадает с первой
   * строкой Далее операция, порожденная матрицей L'' будем обозначать f'' (L''
   * хранится так же в tempQuasigroup)
   */

  for (int i = 1; i < order; i++) {
    while (i != tempQuasigroup->getProduct(i, 0)) {
      tempQuasigroup->swapRows(i, tempQuasigroup->getProduct(i, 0));
    }
  }

  /*
   * (3)
   * Проверяем симметричность L'' (коммутативность f'')
   * Если не симметрична, то квазигруппа не аффинна
   */
  if (!tempQuasigroup->isCommutative()) {
    return false;
  }

  /*
   * (4) Проверяем ассоциативность
   * Если не ассоциативна, то квазигруппа не аффинна
   */
  if (!tempQuasigroup->isAssociative(associativityStrategy)) {
    return false;
  }

  /*
   * (5)
   * Рассматриваем столбец матрицы L, первый элемент которого
   * совпадает с левым верхним элементом L''
   * Обозначаем заданную этим столбцом перестановку (номер столбца) за alpha
   */
  for (int i = 0; i < order; i++) {
    if (getProduct(0, i) == tempQuasigroup->getProduct(0, 0)) {
      alpha = i;
      break;
    }
  }

  /*
   * (6)
   * Рассматриваем строку матрицы L, первый элемент которой
   * совпадает с левым верхним элементом L''
   * Обозначаем заданную этой строкой перестановку (номер строки) за beta
   */
  for (int i = 0; i < order; i++) {
    if (getProduct(i, 0) == tempQuasigroup->getProduct(0, 0)) {
      beta = i;
      break;
    }
  }

  /*
   * (7)
   * Проверяем что alpha и beta сохраняют операцию f'', то есть
   * для любой пары 1 <= i, j <= order, выполнены равенства
   * alpha(f''(qi,qj)) == f''(alpha(qi), alpha(qj))
   * beta(f''(qi,qj)) == f''(beta(qi), beta(qj))
   * Если неравенство хотя бы для одной пары, то неудача
   */
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      if (getProduct(tempQuasigroup->getProduct(i, j), alpha) !=
              tempQuasigroup->getProduct(getProduct(i, alpha),
                                         getProduct(j, alpha)) ||
          getProduct(beta, tempQuasigroup->getProduct(i, j)) !=
              tempQuasigroup->getProduct(getProduct(beta, i),
                                         getProduct(beta, j))) {
        return false;
      }
    }
  }

  /*
   * (8) - (9)
   * Далее элемент в левом верхнем углу L обозначим за c.
   * Проверяем что для любой пары 1 <= i, j <= order
   * выполнено равенство:
   * f(qi,qj) = f''(f''(alpha(qi), beta(qj)), c)
   * Если хотя бы для одной пары неравенство, то квазигруппа не аффинна
   * В противном случае - аффинна.
   */
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      const auto c = getProduct(0, 0);
      const auto left = getProduct(i, j);
      const auto alphaQi = getProduct(i, alpha);
      const auto betaQj = getProduct(beta, j);
      const auto right = tempQuasigroup->getProduct(
          tempQuasigroup->getProduct(alphaQi, betaQj), c);

      if (left != right) {
        return false;
      }
    }
  }

  return true;
}

bool Quasigroup::isSimple() const {
  const int pairsCount = (order * (order - 1)) / 2;

  for (int j = 1; j < order; j++) {
    auto *pairs = new UnorderedPair[pairsCount];
    std::queue<UnorderedPair> unRevEq;
    std::vector<int> classes[order];
    int classIndex[order];
    int equalPairsCount = 0;
    int maxClassSize = 2;
    bool classMost = false;

    int a = 0, b = 0;

    for (int t1 = 0; t1 < order; t1++) {
      for (int t2 = t1 + 1; t2 < order; t2++) {
        pairs[calculateUnorderedPairIndex(t1, t2, order)] = {t1, t2};
      }
      classes[t1].push_back(t1);
      classIndex[t1] = t1;
    }

    mergeUnorderedPairClasses(classes, classIndex, 0, j);
    equalPairsCount++;
    unRevEq.push(pairs[j - 1]);

    if (maxClassSize > order / 2) classMost = true;

    while (unRevEq.size() > 0 && !classMost) {
      a = unRevEq.front().firstElement;
      b = unRevEq.front().secondElement;
      unRevEq.pop();

      for (int i = 0; i < order; i++) {
        const int saLine = getProduct(i, a);
        const int sbLine = getProduct(i, b);
        const int saColumn = getProduct(a, i);
        const int sbColumn = getProduct(b, i);

        if (classIndex[saLine] != classIndex[sbLine]) {
          unRevEq.push(
              pairs[calculateUnorderedPairIndex(saLine, sbLine, order)]);

          // Сливаем классы
          equalPairsCount +=
              static_cast<int>(classes[classIndex[saLine]].size()) *
              static_cast<int>(classes[classIndex[sbLine]].size());
          const int newClassSize = mergeUnorderedPairClasses(
              classes, classIndex, classIndex[saLine], classIndex[sbLine]);
          if (newClassSize > maxClassSize) {
            maxClassSize = newClassSize;
          }
        }

        if (classIndex[saColumn] != classIndex[sbColumn]) {
          unRevEq.push(
              pairs[calculateUnorderedPairIndex(saColumn, sbColumn, order)]);

          // Сливаем классы
          equalPairsCount +=
              static_cast<int>(classes[classIndex[saColumn]].size()) *
              static_cast<int>(classes[classIndex[sbColumn]].size());
          const int newClassSize = mergeUnorderedPairClasses(
              classes, classIndex, classIndex[saColumn], classIndex[sbColumn]);
          if (newClassSize > maxClassSize) {
            maxClassSize = newClassSize;
          }
        }

        if (maxClassSize > order / 2) {
          classMost = true;
          break;
        }
      }
    }

    delete[] pairs;

    if (equalPairsCount != pairsCount && !classMost) {
      return false;
    }
  }

  return true;
}

int Quasigroup::getOrder() const { return order; }

std::ostream &operator<<(std::ostream &out, const Quasigroup &q) {
  for (int i = 0; i < q.order; i++) {
    for (int j = 0; j < q.order; j++) out << q.getProduct(i, j) << " ";
    out << std::endl;
  }
  return out;
}

int Quasigroup::getUnit() { return hasUnit() ? unit : -1; }

std::unordered_set<int> Quasigroup::getGenerationSystem() const {
  auto *generationSystem = new std::unordered_set<int>();
  auto *tempQ = new std::unordered_set<int>();
  auto *newQ = new std::unordered_set<int>();

  generationSystem->insert(0);
  newQ->insert(0);
  for (int i = 1; i < order; i++) {
    tempQ->insert(i);
  }

  int currentSize;
  int currentElement = 0;
  do {
    currentSize = newQ->size();
    currentElement = getProduct(0, currentElement);
    newQ->insert(currentElement);
    if (newQ->size() != currentSize) {
      tempQ->erase(currentElement);
    }
  } while (newQ->size() != currentSize);

  while (!tempQ->empty()) {
    int begin = (*tempQ->begin());
    generationSystem->insert(begin);
    for (const auto &elem : *newQ) {
      newQ->insert(getProduct(elem, begin));
      newQ->insert(getProduct(begin, elem));

      if (tempQ->count(getProduct(elem, begin)) > 0) {
        tempQ->erase(getProduct(elem, begin));
      }

      if (tempQ->count(getProduct(begin, elem)) > 0) {
        tempQ->erase(getProduct(begin, elem));
      }
    }

    newQ->insert(begin);
    tempQ->erase(begin);

    currentElement = begin;
    do {
      currentSize = newQ->size();
      currentElement = getProduct(begin, currentElement);
      newQ->insert(currentElement);
      if (newQ->size() != currentSize) {
        tempQ->erase(currentElement);
      }
    } while (newQ->size() != currentSize);
  }

  return *generationSystem;
}

bool Quasigroup::isPolynomiallyComplete() const {
  return !isAffine() && isSimple();
}

/*
 * (x * y) * x = (z * x) * (y * z)
 */
bool Quasigroup::isQuadratical() const {
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      for (int z = 0; z < getOrder(); z++) {
        if (getProduct(getProduct(x, y), x) !=
            getProduct(getProduct(z, x), getProduct(y, z))) {
          return false;
        }
      }
    }
  }

  return true;
}

/*
 * (x * y) * x = y
 */
bool Quasigroup::isHexagonal() const {
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      if (getProduct(getProduct(x, y), x) != y) {
        return false;
      }
    }
  }

  return true;
}

/*
 * ((x * y) * z) * z = y
 */
bool Quasigroup::isGoldenSquare() const {
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      for (int z = 0; z < getOrder(); z++) {
        if (getProduct(getProduct(getProduct(x, y), z), z) != y) {
          return false;
        }
      }
    }
  }

  return true;
}

/*
 * (x * y) * z = (z * y) * x
 */
bool Quasigroup::isRightModular() const {
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      for (int z = 0; z < getOrder(); z++) {
        if (getProduct(getProduct(x, y), z) !=
            getProduct(getProduct(z, y), x)) {
          return false;
        }
      }
    }
  }

  return true;
}

/*
 * x * (y * z) = z * (y * x)
 */
bool Quasigroup::isLeftModular() const {
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      for (int z = 0; z < getOrder(); z++) {
        if (getProduct(x, getProduct(y, z)) !=
            getProduct(z, getProduct(y, x))) {
          return false;
        }
      }
    }
  }

  return true;
}

/*
 * (x * y) * y = (y * x) * x
 */
bool Quasigroup::isAffineRegularOctagonal() const {
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      if (getProduct(getProduct(x, y), y) != getProduct(getProduct(y, x), x)) {
        return false;
      }
    }
  }

  return true;
}

/*
 * (((x * y) * x) * y) * x = y
 */
bool Quasigroup::isPentagonal() const {
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      if (getProduct(getProduct(getProduct(getProduct(x, y), x), y), x) != y) {
        return false;
      }
    }
  }

  return true;
}

std::string Quasigroup::getRowsConcatenation() const {
  std::string result;
  for (int x = 0; x < order; x++) {
    for (int y = 0; y < order; y++) {
      result += std::to_string(getProduct(x, y));
    }

    if (x != order - 1) {
      result += "||";
    }
  }
  return result;
}

int Quasigroup::associativeTripletsCount() const {
  int result = 0;
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      for (int z = 0; z < getOrder(); z++) {
        const auto isAssociativeTriplet =
            getProduct(getProduct(x, y), z) == getProduct(x, getProduct(y, z));

        if (isAssociativeTriplet) {
          result++;
        }
      }
    }
  }
  return result;
}

int Quasigroup::nonAssociativeTripletsCount() const {
  return getOrder() * getOrder() * getOrder() - associativeTripletsCount();
}

int Quasigroup::commutativePairsCount() const {
  int result = 0;
  for (int x = 0; x < getOrder(); x++) {
    for (int y = 0; y < getOrder(); y++) {
      if (getProduct(x, y) == getProduct(y, x)) {
        result++;
      }
    }
  }
  return result;
}

int Quasigroup::nonCommutativePairsCount() const {
  return getOrder() * getOrder() - commutativePairsCount();
}

bool operator==(const Quasigroup &left, const Quasigroup &right) {
  return left.getRowsConcatenation() == right.getRowsConcatenation();
}

bool operator!=(const Quasigroup &left, const Quasigroup &right) {
  return !(left == right);
}

bool operator<(const Quasigroup &left, const Quasigroup &right) {
  return left.getRowsConcatenation() < right.getRowsConcatenation();
}

bool operator<=(const Quasigroup &left, const Quasigroup &right) {
  return left.getRowsConcatenation() <= right.getRowsConcatenation();
}

bool operator>(const Quasigroup &left, const Quasigroup &right) {
  return right < left;
}

bool operator>=(const Quasigroup &left, const Quasigroup &right) {
  return right <= left;
}

size_t Quasigroup::QuasigroupHash::operator()(
    const Quasigroup *quasigroup) const {
  constexpr std::hash<std::string> hasher;
  std::string hash;
  for (int y = 0; y < quasigroup->getOrder(); y++) {
    for (int x = 0; x < quasigroup->getOrder(); x++) {
      hash += std::to_string(quasigroup->getProduct(x, y)) + " ";
    }
    hash += "\n";
  }
  return hasher(hash);
}

bool Quasigroup::QuasigroupEqualHash::operator()(const Quasigroup *q1,
                                                 const Quasigroup *q2) const {
  constexpr QuasigroupHash hashCode;
  return hashCode(q1) == hashCode(q2);
}
}  // namespace Quasigroup
