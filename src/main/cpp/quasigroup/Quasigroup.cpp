#include "Quasigroup.h"

#include <cstdlib>
#include <cstring>
#include <memory>
#include <ostream>
#include <queue>
#include <random>
#include <unordered_set>

#include "LatinSquareQuasigroup.h"
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

bool Quasigroup::hasUnit() const {
  for (int e = 0; e < order; e++) {
    auto count = 0;
    for (int x = 0; x < order; x++) {
      if (getProduct(e, x) != x || getProduct(x, e) != x) {
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

bool Quasigroup::isLoop() const { return hasUnit(); }

bool Quasigroup::isGroup() const {
  return isLoop() && isAssociativeByLightTest();
}

bool Quasigroup::isAbelianGroup() const { return isGroup() && isCommutative(); }

bool Quasigroup::containsProperSubquasigroup() const {
  unsigned int *sqg;
  sqg = nullptr;
  constexpr auto properBorder = 1;

  const int findSubgroupResult = findSubquasigroup(properBorder, &sqg);
  if (sqg != nullptr) {
    free(sqg);
  }

  return findSubgroupResult > 0;
}

/*
 * A quasigroup (Q, ∗) of order N is said to be shapeless iff it is
 * non-idempotent, non-commutative, non-associative, it does not
 * have neither left nor right unit, it does not contain proper (non-trivial)
 * sub-quasigroups, and there is no k < 2N such that identities of the
 * kinds x * (x * ... * (x  * y)) = y, y = ((y * x) * ... * x) (k times)
 */
bool Quasigroup::isShapeless() const {
  return !isIdempotent() && !isCommutative() && !isAssociativeByLightTest() &&
         !hasLeftUnit() && !hasRightUnit() && !containsProperSubquasigroup() &&
         !oneOfShapelessIdentitiesIsSatisfied();
}

bool Quasigroup::oneOfShapelessIdentitiesIsSatisfied() const {
  for (int k = 1; k < 2 * order; k++) {
    if (oneOfShapelessIdentitiesIsSatisfiedForK(k)) {
      return true;
    }
  }

  return false;
}

bool Quasigroup::oneOfShapelessIdentitiesIsSatisfiedForK(const int k) const {
  auto leftProductIsSatisfied = true;
  auto rightProductIsSatisfied = true;

  for (int x = 0; x < order; x++) {
    for (int y = 0; y < order; y++) {
      auto leftProduct = y;
      auto rightProduct = y;

      for (int i = 0; i < k; i++) {
        leftProduct = getProduct(x, leftProduct);
        rightProduct = getProduct(rightProduct, x);
      }

      leftProductIsSatisfied = leftProductIsSatisfied && (leftProduct == y);
      rightProductIsSatisfied = rightProductIsSatisfied && (rightProduct == y);

      if (!leftProductIsSatisfied && !rightProductIsSatisfied) {
        return false;
      }
    }
  }

  return true;
}

bool Quasigroup::isAssociative(
    AssociativityDeterminationStrategy associativityStrategy) const {
  switch (associativityStrategy) {
    case AssociativityDeterminationStrategy::LightTest:
      return isAssociativeByLightTest();
    case AssociativityDeterminationStrategy::CompleteSearch:
      return isAssociativeByCompleteSearch();
    case AssociativityDeterminationStrategy::Basis4Associativity:
      return isAssociativeByBasis4Associativity();
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

bool Quasigroup::isAssociativeByBasis4Associativity() const {
  const std::unordered_set<int> S = findBasis();

  if (S.size() > 3 * std::sqrt(order)) return false;

  std::unordered_set<int> S2;
  for (const int a : S)
    for (const int b : S) S2.insert(getProduct(a, b));

  if (S2.size() != order) return false;

  return check4Associativity(S);
}

bool Quasigroup::check4Associativity(const std::unordered_set<int> &S) const {
  const std::vector Sv(S.begin(), S.end());
  const size_t m = Sv.size();

  for (size_t i = 0; i < m; i++) {
    const int a = Sv[i];
    for (size_t j = 0; j < m; j++) {
      const int b = Sv[j];
      const int ab = getProduct(a, b);

      for (size_t k = 0; k < m; k++) {
        const int c = Sv[k];
        const int bc = getProduct(b, c);
        const int abc = getProduct(ab, c);

        for (size_t l = 0; l < m; l++) {
          const int d = Sv[l];
          const int cd = getProduct(c, d);
          const int bcd = getProduct(bc, d);

          const int v1 = getProduct(abc, d);
          const int v2 = getProduct(ab, cd);

          if (const int v4 = getProduct(a, bcd); v1 != v2 || v2 != v4)
            return false;

          const int v3 = getProduct(getProduct(a, bc), d);
          if (v2 != v3) return false;

          if (const int v5 = getProduct(a, getProduct(b, cd)); v3 != v5)
            return false;
        }
      }
    }
  }
  return true;
}

std::unordered_set<int> Quasigroup::findBasis() const {
  const double ell = std::sqrt(order / 2.0);

  std::vector<int> elemToGlobal(order);
  for (int i = 0; i < order; i++) {
    elemToGlobal[i] = i;
  }

  auto operation = [this](const int x, const int y) {
    return getProduct(x, y);
  };

  auto [A, B] = groupDecomposition(order, ell, elemToGlobal, operation);

  std::unordered_set<int> S = A;
  S.insert(B.begin(), B.end());
  return S;
}

std::pair<std::unordered_set<int>, std::unordered_set<int>>
Quasigroup::groupDecomposition(
    int suborder, double ell, const std::vector<int> &elemToGlobal,
    const std::function<int(int, int)> &operation) const {
  double n = suborder;

  if (ell > n) ell = n;
  if (ell < 1.0) ell = 1.0;

  bool isPrime = true;
  for (int d = 2; d * d <= suborder; d++) {
    if (suborder % d == 0) {
      isPrime = false;
      break;
    }
  }

  if (isPrime) {
    int g = 1;
    int q = std::floor(n / ell);

    auto pow = [&](const int base, int exp) {
      int result = 0;
      int b = base;
      while (exp > 0) {
        if (exp & 1) result = operation(result, b);
        b = operation(b, b);
        exp >>= 1;
      }
      return result;
    };

    std::unordered_set<int> A, B;

    int current = 0;
    for (int i = 0; i < q; i++) {
      B.insert(elemToGlobal[current]);
      current = operation(current, g);
    }

    int gq = pow(g, q);
    int max_a = std::floor(n / q);
    current = 0;
    for (int a = 0; a <= max_a; a++) {
      A.insert(elemToGlobal[current]);
      current = operation(current, gq);
    }

    return {A, B};
  }

  std::unordered_set<int> HLocal = findLargeSubgroup(suborder, operation);
  double hSize = HLocal.size();

  std::vector Hv(HLocal.begin(), HLocal.end());
  std::sort(Hv.begin(), Hv.end());

  std::vector<int> HToGlobal(Hv.size());
  std::unordered_map<int, int> globalToH;
  for (size_t i = 0; i < Hv.size(); i++) {
    HToGlobal[i] = elemToGlobal[Hv[i]];
    globalToH[Hv[i]] = i;
  }

  auto operationH = [&](const int x, const int y) {
    const int oldX = Hv[x];
    const int oldY = Hv[y];
    const int oldResult = operation(oldX, oldY);
    return globalToH.at(oldResult);
  };

  if (hSize > n / ell) {
    double ellPrime = ell * hSize / n;

    auto [APrime, BPrime] = groupDecomposition(static_cast<int>(Hv.size()),
                                               ellPrime, HToGlobal, operationH);

    std::unordered_set<int> TLocal =
        leftTransversal(suborder, HLocal, operation);

    std::unordered_set<int> AGlobal, BGlobal;
    for (int t : TLocal) {
      int tGlobal = elemToGlobal[t];
      for (int a : APrime) {
        AGlobal.insert(getProduct(tGlobal, a));
      }
    }
    for (int b : BPrime) {
      BGlobal.insert(b);
    }

    return {AGlobal, BGlobal};
  }

  if (hSize >= n / (2 * ell)) {
    std::unordered_set<int> T_local =
        leftTransversal(suborder, HLocal, operation);

    std::unordered_set<int> T_global, H_global;
    for (int t : T_local) T_global.insert(elemToGlobal[t]);
    for (int h : HLocal) H_global.insert(elemToGlobal[h]);

    return {T_global, H_global};
  }

  auto [A_prime, B_prime] = groupDecomposition(static_cast<int>(Hv.size()), ell,
                                               HToGlobal, operationH);

  std::unordered_set<int> T_local =
      rightTransversal(suborder, HLocal, operation);

  std::unordered_set<int> A_global, B_global;
  for (int a : A_prime) {
    A_global.insert(a);
  }
  for (int b : B_prime) {
    for (int t : T_local) {
      int t_global = elemToGlobal[t];
      B_global.insert(getProduct(b, t_global));
    }
  }

  return {A_global, B_global};
}

std::unordered_set<int> Quasigroup::findLargeSubgroup(
    const int suborder, const std::function<int(int, int)> &operation) const {
  const int target = std::ceil(std::sqrt(suborder));

  for (int g = 1; g < suborder; g++) {
    int current = g;
    int ord = 1;
    while (current != 0) {
      current = operation(current, g);
      ord++;
    }
    if (ord >= target && ord < suborder) {
      std::unordered_set<int> H;
      current = 0;
      for (int i = 0; i < ord; i++) {
        H.insert(current);
        current = operation(current, g);
      }
      return H;
    }
  }

  std::vector inH(suborder, false);
  std::vector<int> H_elements;
  inH[0] = true;
  H_elements.push_back(0);

  for (int g = 1; g < suborder; g++) {
    if (inH[g]) continue;
    const size_t current_size = H_elements.size();
    for (size_t i = 0; i < current_size; i++) {
      int y = operation(H_elements[i], g);
      if (!inH[y]) {
        inH[y] = true;
        H_elements.push_back(y);
      }
    }
    if (H_elements.size() >= target) break;
  }

  if (H_elements.size() >= target && H_elements.size() < suborder) {
    return std::unordered_set(H_elements.begin(), H_elements.end());
  }

  std::unordered_set<int> H;
  for (int i = 0; i < suborder; i++) H.insert(i);
  return H;
}

std::unordered_set<int> Quasigroup::leftTransversal(
    const int suborder, const std::unordered_set<int> &H,
    const std::function<int(int, int)> &operation) const {
  std::vector used(suborder, false);
  std::unordered_set<int> transversal;
  const std::vector Hv(H.begin(), H.end());

  for (int g = 0; g < suborder; g++) {
    if (used[g]) continue;
    transversal.insert(g);
    for (const int h : Hv) {
      used[operation(g, h)] = true;
    }
  }
  return transversal;
}

std::unordered_set<int> Quasigroup::rightTransversal(
    int suborder, const std::unordered_set<int> &H,
    const std::function<int(int, int)> &operation) const {
  return leftTransversal(
      suborder, H, [&](const int x, const int y) { return operation(y, x); });
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

int Quasigroup::findSubquasigroup(const int border, unsigned int **a_sq) const {
  unsigned int *a_sqi;
  int last;

  *a_sq = nullptr;
  unsigned int *a_q = nullptr;
  int retval = -1;

  const auto seed =
      static_cast<unsigned int *>(malloc(border * sizeof(unsigned int)));
  if (seed == nullptr) {
    printf("Failed to allocate memory\n");
    return -1;
  }

  do {
    *a_sq = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * order));
    a_sqi = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * order));
    if (a_sqi == nullptr) {
      printf("Failed to allocate memory\n");
      break;
    }
    a_q = static_cast<unsigned int *>(malloc(sizeof(unsigned int) * order));
    if (a_q == nullptr) {
      printf("Failed to allocate memory\n");
      break;
    }

    for (int i = 0; i < border; i++) {
      seed[i] = static_cast<unsigned int>(i);
    }

    do {
      retval = checkStep(seed, border, *a_sq, a_sqi, a_q);
      if (retval != 0) {
        break;
      }
      last = nextStep(seed, border);
      retval = checkStep(seed, border, *a_sq, a_sqi, a_q);
    } while (last == 0);
  } while (false);

  free(seed);
  if (*a_sq != nullptr && retval <= 0) {
    free(*a_sq);
    *a_sq = nullptr;
  }
  if (a_sqi != nullptr) {
    free(a_sqi);
  }
  if (a_q != nullptr) {
    free(a_q);
  }

  return retval;
}

int Quasigroup::nextStep(unsigned int *step, const int border) const {
  int i;

  for (i = border - 1; i >= 0; i--) {
    if (step[i] < (order - 1) - (border - 1 - i)) {
      break;
    }
  }

  step[i]++;
  int cur = step[i] + 1;
  for (i = i + 1; i < border; i++) {
    step[i] = cur;
    cur++;
  }

  if (step[0] == order - border) {
    return 1;
  }
  return 0;
}

int Quasigroup::checkStep(const unsigned int *step, const int border,
                          unsigned int *a_sq, unsigned int *a_sqi,
                          unsigned int *a_q) const {
  int i;

  int sqLen = border;
  int first = 0;
  int last = border;
  int retval = 0;

  // initialization
  memset(a_sq, 0, sizeof(unsigned int) * order);
  memset(a_sqi, 0, sizeof(unsigned int) * order);
  memset(a_q, 0, sizeof(unsigned int) * order);
  for (i = 0; i < border; i++) {
    a_sq[i] = step[i];
    a_sqi[step[i]] = 3;
    a_q[i] = step[i];
  }

  // build the closure of the seed
  while (last - first > 0) {
    const unsigned int cur = a_q[first];
    first++;

    unsigned int tmp = getProduct(cur, cur);
    if (a_sqi[tmp] == 0) {
      a_q[last] = tmp;
      a_sqi[tmp] = 2;
      last++;
    }

    for (i = 0; i < sqLen; i++) {
      tmp = getProduct(a_sq[i], cur);
      if (a_sqi[tmp] == 0) {
        a_q[last] = tmp;
        a_sqi[tmp] = 2;
        last++;
      }
      tmp = getProduct(cur, a_sq[i]);
      if (a_sqi[tmp] == 0) {
        a_q[last] = tmp;
        a_sqi[tmp] = 2;
        last++;
      }
    }

    if ((a_sqi[cur] % 2) == 0) {
      a_sq[sqLen] = cur;
      a_sqi[cur] = 1;
      sqLen++;
    }
  }
  if (last - first + sqLen <= order / 2) {
    // a subquasigroup is found
    retval = sqLen;
  }

  return retval;
}

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