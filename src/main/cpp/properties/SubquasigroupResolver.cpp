#include "SubquasigroupResolver.h"

#include <cstring>

namespace Quasigroup {

bool SubquasigroupResolver::containsProperSubquasigroup(const Quasigroup *q,
                                                        const int border) {
  unsigned int *sqg;
  sqg = nullptr;

  const int findSubgroupResult = findSubquasigroup(q, border, &sqg);
  if (sqg != nullptr) {
    free(sqg);
  }

  return findSubgroupResult > 0;
}
bool SubquasigroupResolver::containsNonTrivialProperSubquasigroup(
    const Quasigroup *q) {
  return containsProperSubquasigroup(q, 2);
}

bool SubquasigroupResolver::containsAnyProperSubquasigroup(
    const Quasigroup *q) {
  return containsProperSubquasigroup(q, 1);
}

int SubquasigroupResolver::findSubquasigroup(const Quasigroup *q,
                                             const int border,
                                             unsigned int **a_sq) {
  int last;

  *a_sq = nullptr;
  unsigned int *a_sqi = nullptr;
  int retval = -1;

  const auto seed =
      static_cast<unsigned int *>(malloc(border * sizeof(unsigned int)));
  if (seed == nullptr) {
    printf("Failed to allocate memory\n");
    return -1;
  }

  do {
    *a_sq = static_cast<unsigned int *>(
        malloc(sizeof(unsigned int) * q->getOrder()));
    a_sqi = static_cast<unsigned int *>(
        malloc(sizeof(unsigned int) * q->getOrder()));
    if (a_sqi == nullptr) {
      printf("Failed to allocate memory\n");
      break;
    }

    for (int i = 0; i < border; i++) {
      seed[i] = static_cast<unsigned int>(i);
    }

    retval = checkSeed(q, seed, border, *a_sq, a_sqi);
    if (retval != 0) {
      break;
    }
    do {
      last = getNextSeed(q, seed, border);
      retval = checkSeed(q, seed, border, *a_sq, a_sqi);
      if (retval != 0) {
        break;
      }
    } while (last == 0);
  } while (false);

  free(seed);
  if (*a_sq != nullptr && (retval <= 0)) {
    free(*a_sq);
    *a_sq = nullptr;
  }
  if (a_sqi != nullptr) {
    free(a_sqi);
  }

  return retval;
}

int SubquasigroupResolver::getNextSeed(const Quasigroup *q, unsigned int *seed,
                                       const int border) {
  int i;

  for (i = border - 1; i >= 0; i--) {
    if (seed[i] < (q->getOrder() - 1) - (border - 1 - i)) {
      break;
    }
  }
  seed[i]++;
  int cur = seed[i] + 1;
  for (i = i + 1; i < border; i++) {
    seed[i] = cur;
    cur++;
  }

  if (seed[0] == q->getOrder() - border) {
    return 1;
  }
  return 0;
}

int SubquasigroupResolver::checkSeed(const Quasigroup *q,
                                     const unsigned int *seed, const int border,
                                     unsigned int *a_sq, unsigned int *a_sqi) {
  int i;

  int retval = 0;

  if (border >= q->getOrder()) {
    printf("Subquasigroup order %d must be less than quasigroup order %d\n",
           border, q->getOrder());
    return -1;
  }

  // initialization
  memset(a_sq, 0, sizeof(unsigned int) * q->getOrder());   // subquasigroup
  memset(a_sqi, 0, sizeof(unsigned int) * q->getOrder());  // covered
  for (i = 0; i < border; i++) {
    a_sq[i] = seed[i];
    a_sqi[seed[i]] = 3;
  }

  // build the closure of the seed
  int covered_num = border;
  unsigned int cur = q->getProduct(a_sq[0], a_sq[0]);
  if (a_sqi[cur] != 3) {  // uncovered
    a_sqi[cur] = 3;
    a_sq[covered_num] = cur;
    covered_num++;
  }
  int checked_num = 1;

  while ((covered_num <= q->getOrder() / 2) && (checked_num < covered_num)) {
    for (i = 0; i < checked_num; i++) {
      cur = q->getProduct(a_sq[i], a_sq[checked_num]);
      if (a_sqi[cur] != 3) {
        a_sqi[cur] = 3;
        a_sq[covered_num] = cur;
        covered_num++;
        if (covered_num > q->getOrder() / 2) {
          break;
        }
      }
      cur = q->getProduct(a_sq[checked_num], a_sq[i]);
      if (a_sqi[cur] != 3) {
        a_sqi[cur] = 3;
        a_sq[covered_num] = cur;
        covered_num++;
        if (covered_num > q->getOrder() / 2) {
          break;
        }
      }
    }
    cur = q->getProduct(a_sq[checked_num], a_sq[checked_num]);
    if (a_sqi[cur] != 3) {
      a_sqi[cur] = 3;
      a_sq[covered_num] = cur;
      covered_num++;
    }
    checked_num++;
  }
  if (covered_num <= q->getOrder() / 2) {
    // a subquasigroup is found
    retval = covered_num;
  }

  return retval;
}

}  // namespace Quasigroup