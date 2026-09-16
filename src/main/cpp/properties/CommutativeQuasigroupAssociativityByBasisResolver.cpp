#include "CommutativeQuasigroupAssociativityByBasisResolver.h"

#include "utils/Helper.h"

namespace Quasigroup {
int CommutativeQuasigroupAssociativityByBasisResolver::findLocalUnit(
    const int n, const std::function<int(int, int)> &op) {
  int e = -1;
  for (int x = 0; x < n; ++x) {
    if (op(0, x) == 0) {
      e = x;
      break;
    }
  }

  if (e == -1) return -1;

  for (int x = 0; x < n; ++x) {
    if (op(e, x) != x || op(x, e) != x) {
      return -1;
    }
  }

  return e;
}

bool CommutativeQuasigroupAssociativityByBasisResolver::isSubgroup(
    const std::unordered_set<int> &H, const std::function<int(int, int)> &op) {
  if (H.empty()) return false;

  int maxElement = -1;
  for (int x : H) {
    if (x < 0) return false;
    maxElement = std::max(maxElement, x);
  }

  std::vector<unsigned char> belongs(static_cast<std::size_t>(maxElement) + 1,
                                     0);

  for (const int x : H) {
    belongs[x] = 1;
  }

  for (const int a : H) {
    for (const int b : H) {
      if (const int c = op(a, b); c < 0 || c > maxElement || !belongs[c]) {
        return false;
      }
    }
  }

  return true;
}

bool CommutativeQuasigroupAssociativityByBasisResolver::isAssociative(
    Quasigroup *q) {
  if (!q->hasUnit()) return false;
  if (q->getOrder() == 1) return true;

  const auto maybeS = findBasis(q);
  if (!maybeS.has_value()) return false;

  const auto &S = *maybeS;

  if (S.empty() ||
      static_cast<long double>(S.size()) >
          3.0L * std::sqrt(static_cast<long double>(q->getOrder()))) {
    return false;
  }

  for (const int a : S) {
    if (a < 0 || a >= q->getOrder()) return false;
  }

  std::vector<unsigned char> covered(q->getOrder(), 0);
  int coveredCount = 0;

  for (const int a : S) {
    for (const int b : S) {
      const int c = q->getProduct(a, b);
      if (c < 0 || c >= q->getOrder()) return false;

      if (!covered[c]) {
        covered[c] = 1;
        ++coveredCount;
      }
    }
  }

  if (coveredCount != q->getOrder()) return false;

  return checkAssociativityOnBasis(q, S);
}

bool CommutativeQuasigroupAssociativityByBasisResolver::
    checkAssociativityOnBasis(const Quasigroup *q,
                              const std::unordered_set<int> &S) {
  std::vector basis(S.begin(), S.end());
  std::sort(basis.begin(), basis.end());

  const std::size_t k = basis.size();

  std::vector<int> products(k * k);
  for (std::size_t i = 0; i < k; ++i) {
    for (std::size_t j = 0; j < k; ++j) {
      products[i * k + j] = q->getProduct(basis[i], basis[j]);
    }
  }

  for (int x = 0; x < q->getOrder(); ++x) {
    for (std::size_t i = 0; i < k; ++i) {
      const int xa = q->getProduct(x, basis[i]);

      for (std::size_t j = 0; j < k; ++j) {
        if (q->getProduct(xa, basis[j]) !=
            q->getProduct(x, products[i * k + j])) {
          return false;
        }
      }
    }
  }

  return true;
}

std::unordered_set<int>
CommutativeQuasigroupAssociativityByBasisResolver::findLargeSubgroup(
    const int suborder, const std::function<int(int, int)> &operation) {
  const int n = suborder;

  if (n <= 1 || isPrime(n)) return {};

  const int e = findLocalUnit(n, operation);
  if (e == -1) return {};

  int target = static_cast<int>(std::sqrt(static_cast<double>(n)));
  while (1LL * target * target < n) ++target;

  std::vector<std::vector<int>> powers(n);
  powers[e] = {e};

  for (int g = 0; g < n; ++g) {
    if (g == e) continue;

    auto &p = powers[g];
    p.push_back(e);

    int current = e;
    bool returnedToUnit = false;

    for (int r = 1; r <= n; ++r) {
      current = operation(current, g);
      if (current < 0 || current >= n) return {};

      if (current == e) {
        returnedToUnit = true;
        break;
      }

      p.push_back(current);
    }

    if (!returnedToUnit) return {};

    const int r = static_cast<int>(p.size());

    if (r < target) continue;

    if (r < n) {
      return std::unordered_set(p.begin(), p.end());
    }

    int primeDivisor = 2;
    while (n % primeDivisor != 0) {
      ++primeDivisor;
    }

    std::unordered_set<int> H;
    H.reserve(static_cast<std::size_t>(n / primeDivisor));

    for (int i = 0; i < n; i += primeDivisor) {
      H.insert(p[i]);
    }

    return H;
  }

  std::vector H{e};
  std::vector<unsigned char> inH(n, 0);
  inH[e] = 1;

  while (H.size() < static_cast<std::size_t>(target)) {
    int g = -1;

    for (int x = 0; x < n; ++x) {
      if (!inH[x]) {
        g = x;
        break;
      }
    }

    if (g == -1) return {};

    std::vector<int> nextH;
    std::vector<unsigned char> inNextH(n, 0);

    for (int h : H) {
      for (int c : powers[g]) {
        const int value = operation(h, c);
        if (value < 0 || value >= n) return {};

        if (!inNextH[value]) {
          inNextH[value] = 1;
          nextH.push_back(value);
        }
      }
    }

    for (const int h : H) {
      if (!inNextH[h]) return {};
    }

    if (nextH.size() < 2 * H.size() ||
        nextH.size() >= static_cast<std::size_t>(n)) {
      return {};
    }

    H = std::move(nextH);
    inH = std::move(inNextH);
  }

  return std::unordered_set(H.begin(), H.end());
}

std::pair<std::unordered_set<int>, std::unordered_set<int>>
CommutativeQuasigroupAssociativityByBasisResolver::groupDecomposition(
    int n, double ell, const std::function<int(int, int)> &op) {
  if (n <= 0 || !std::isfinite(ell) || ell < 1.0 ||
      ell > static_cast<double>(n)) {
    return {{}, {}};
  }

  const int e = findLocalUnit(n, op);
  if (e == -1) return {{}, {}};

  if (n == 1) {
    return {{e}, {e}};
  }

  if (isPrime(n)) {
    const int g = (e == 0 ? 1 : 0);

    std::vector<int> powers(n);
    std::vector<unsigned char> seen(n, 0);

    int current = e;

    for (int i = 0; i < n; ++i) {
      if (current < 0 || current >= n || seen[current]) {
        return {{}, {}};
      }

      powers[i] = current;
      seen[current] = 1;
      current = op(current, g);
    }

    if (current != e) return {{}, {}};

    const int q = std::clamp(static_cast<int>(std::floor(n / ell)), 1, n);

    std::unordered_set<int> A;
    std::unordered_set<int> B;

    B.reserve(static_cast<std::size_t>(q));

    for (int i = 0; i < q; ++i) {
      B.insert(powers[i]);
    }

    for (long long i = 0; i < n; i += q) {
      A.insert(powers[static_cast<std::size_t>(i)]);
    }

    return {std::move(A), std::move(B)};
  }

  auto H = findLargeSubgroup(n, op);

  int target = static_cast<int>(std::sqrt(static_cast<double>(n)));
  while (1LL * target * target < n) ++target;

  const std::size_t h = H.size();

  if (h < static_cast<std::size_t>(target) ||
      h > static_cast<std::size_t>(n / 2) || n % static_cast<int>(h) != 0) {
    return {{}, {}};
  }

  std::vector Hlist(H.begin(), H.end());
  std::sort(Hlist.begin(), Hlist.end());

  std::vector index(n, -1);
  for (std::size_t i = 0; i < h; ++i) {
    const int value = Hlist[i];
    if (value < 0 || value >= n) return {{}, {}};
    index[value] = static_cast<int>(i);
  }

  if (index[e] == -1) return {{}, {}};

  std::vector<int> tableH(h * h);

  for (std::size_t i = 0; i < h; ++i) {
    for (std::size_t j = 0; j < h; ++j) {
      const int value = op(Hlist[i], Hlist[j]);

      if (value < 0 || value >= n || index[value] == -1) {
        return {{}, {}};
      }

      tableH[i * h + j] = index[value];
    }
  }

  std::vector<int> Tlist;
  std::vector<unsigned char> used(n, 0);

  const std::size_t expectedCosets = static_cast<std::size_t>(n) / h;

  Tlist.reserve(expectedCosets);

  for (int g = 0; g < n; ++g) {
    if (used[g]) continue;

    if (Tlist.size() == expectedCosets) {
      return {{}, {}};
    }

    Tlist.push_back(g);

    for (int value : Hlist) {
      const int product = op(g, value);

      if (product < 0 || product >= n || used[product]) {
        return {{}, {}};
      }

      used[product] = 1;
    }
  }

  if (Tlist.size() != expectedCosets) {
    return {{}, {}};
  }

  const auto hSize = static_cast<double>(h);
  const double bLimit = static_cast<double>(n) / ell;

  if (hSize <= bLimit && hSize >= bLimit / 2.0) {
    std::unordered_set T(Tlist.begin(), Tlist.end());
    return {std::move(T), std::move(H)};
  }

  const bool enlargeA = hSize > bLimit;

  double recursiveEll = enlargeA ? ell * hSize / static_cast<double>(n) : ell;

  recursiveEll = std::clamp(recursiveEll, 1.0, hSize);

  const auto opH = [&tableH, h](int x, int y) -> int {
    return tableH[static_cast<std::size_t>(x) * h +
                  static_cast<std::size_t>(y)];
  };

  auto [APrime, BPrime] =
      groupDecomposition(static_cast<int>(h), recursiveEll, opH);

  if (APrime.empty() || BPrime.empty()) {
    return {{}, {}};
  }

  for (int x : APrime) {
    if (x < 0 || static_cast<std::size_t>(x) >= h) {
      return {{}, {}};
    }
  }

  for (int x : BPrime) {
    if (x < 0 || static_cast<std::size_t>(x) >= h) {
      return {{}, {}};
    }
  }

  std::unordered_set<int> A;
  std::unordered_set<int> B;

  if (enlargeA) {
    for (int t : Tlist) {
      for (int a : APrime) {
        const int value = op(t, Hlist[a]);
        if (value < 0 || value >= n) return {{}, {}};
        A.insert(value);
      }
    }

    for (int b : BPrime) {
      B.insert(Hlist[b]);
    }
  } else {
    for (int a : APrime) {
      A.insert(Hlist[a]);
    }

    for (int b : BPrime) {
      for (int t : Tlist) {
        const int value = op(Hlist[b], t);
        if (value < 0 || value >= n) return {{}, {}};
        B.insert(value);
      }
    }
  }

  return {std::move(A), std::move(B)};
}

std::optional<std::unordered_set<int>>
CommutativeQuasigroupAssociativityByBasisResolver::findBasis(Quasigroup *q) {
  if (q->getOrder() <= 0 || !q->hasUnit()) {
    return std::nullopt;
  }

  if (q->getOrder() == 1) {
    return std::unordered_set{q->getUnit()};
  }

  const double ell = std::sqrt(static_cast<double>(q->getOrder()) / 2.0);

  const auto op = [q](const int x, const int y) { return q->getProduct(x, y); };

  auto [A, B] = groupDecomposition(q->getOrder(), ell, op);

  if (A.empty() || B.empty()) {
    return std::nullopt;
  }

  A.insert(B.begin(), B.end());
  return A;
}
}  // namespace Quasigroup