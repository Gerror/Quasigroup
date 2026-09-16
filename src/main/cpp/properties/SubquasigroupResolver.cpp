#include "SubquasigroupResolver.h"

#include <cstring>

namespace Quasigroup {

bool SubquasigroupResolver::containsProperSubquasigroup(const Quasigroup *q) {
  unsigned int *sqg;
  sqg = nullptr;
  constexpr auto properBorder = 1;

  const int findSubgroupResult = findSubquasigroup(q, properBorder, &sqg);
  if (sqg != nullptr) {
    free(sqg);
  }

  return findSubgroupResult > 0;
}

int SubquasigroupResolver::findSubquasigroup(const Quasigroup *q,
                                             const int border,
                                             unsigned int **a_sq) {
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
    *a_sq = static_cast<unsigned int *>(
        malloc(sizeof(unsigned int) * q->getOrder()));
    a_sqi = static_cast<unsigned int *>(
        malloc(sizeof(unsigned int) * q->getOrder()));
    if (a_sqi == nullptr) {
      printf("Failed to allocate memory\n");
      break;
    }
    a_q = static_cast<unsigned int *>(
        malloc(sizeof(unsigned int) * q->getOrder()));
    if (a_q == nullptr) {
      printf("Failed to allocate memory\n");
      break;
    }

    for (int i = 0; i < border; i++) {
      seed[i] = static_cast<unsigned int>(i);
    }

    do {
      retval = checkStep(q, seed, border, *a_sq, a_sqi, a_q);
      if (retval != 0) {
        break;
      }
      last = nextStep(q, seed, border);
      retval = checkStep(q, seed, border, *a_sq, a_sqi, a_q);
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

int SubquasigroupResolver::nextStep(const Quasigroup *q, unsigned int *step,
                                    const int border) {
  int i;

  for (i = border - 1; i >= 0; i--) {
    if (step[i] < (q->getOrder() - 1) - (border - 1 - i)) {
      break;
    }
  }

  step[i]++;
  int cur = step[i] + 1;
  for (i = i + 1; i < border; i++) {
    step[i] = cur;
    cur++;
  }

  if (step[0] == q->getOrder() - border) {
    return 1;
  }
  return 0;
}

int SubquasigroupResolver::checkStep(const Quasigroup *q,
                                     const unsigned int *step, const int border,
                                     unsigned int *a_sq, unsigned int *a_sqi,
                                     unsigned int *a_q) {
  int i;

  int sqLen = border;
  int first = 0;
  int last = border;
  int retval = 0;

  // initialization
  memset(a_sq, 0, sizeof(unsigned int) * q->getOrder());
  memset(a_sqi, 0, sizeof(unsigned int) * q->getOrder());
  memset(a_q, 0, sizeof(unsigned int) * q->getOrder());
  for (i = 0; i < border; i++) {
    a_sq[i] = step[i];
    a_sqi[step[i]] = 3;
    a_q[i] = step[i];
  }

  // build the closure of the seed
  while (last - first > 0) {
    const unsigned int cur = a_q[first];
    first++;

    unsigned int tmp = q->getProduct(cur, cur);
    if (a_sqi[tmp] == 0) {
      a_q[last] = tmp;
      a_sqi[tmp] = 2;
      last++;
    }

    for (i = 0; i < sqLen; i++) {
      tmp = q->getProduct(a_sq[i], cur);
      if (a_sqi[tmp] == 0) {
        a_q[last] = tmp;
        a_sqi[tmp] = 2;
        last++;
      }
      tmp = q->getProduct(cur, a_sq[i]);
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
  if (last - first + sqLen <= q->getOrder() / 2) {
    // a subquasigroup is found
    retval = sqLen;
  }

  return retval;
}

}  // namespace Quasigroup