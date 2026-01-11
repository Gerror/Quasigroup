#include "KepkaTransformer.h"

#include <quasigroup/square/LatinSquareQuasigroup.h>
#include <utils/Helper.h>

#include <random>
#include <set>

namespace Quasigroup {
Quasigroup *KepkaTransformer::transform(const Quasigroup *original) {
  const auto result = new LatinSquareQuasigroup(*original);

  std::vector<int> full(original->getOrder());
  std::iota(std::begin(full), std::end(full), 0);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> rDistribution(1, original->getOrder() - 3);

  auto r = rDistribution(gen);
  if (r % 2 == 1 && original->getOrder() % 2 == 1) {
    r++;
  }

  std::vector<int> firstCycle(r);
  std::sample(full.begin(), full.end(), firstCycle.begin(), r, gen);

  const std::set firstCycleSet(firstCycle.begin(), firstCycle.end());
  std::set secondCycleSet(full.begin(), full.end());

  for (int i : firstCycleSet) {
    secondCycleSet.erase(i);
  }

  std::vector secondCycle(secondCycleSet.begin(), secondCycleSet.end());

  std::uniform_int_distribution<> bDistribution(0, secondCycle.size() - 1);
  const auto b = secondCycle[bDistribution(gen)];

  firstCycle.push_back(b);

  std::shuffle(firstCycle.begin(), firstCycle.end(), gen);
  std::shuffle(secondCycle.begin(), secondCycle.end(), gen);

  const auto firstFixLine =
      transmutationFromCycle(firstCycle, original->getOrder());
  const auto secondFixLine =
      transmutationFromCycle(secondCycle, original->getOrder());

  result->setColumn(0, secondFixLine);
  result->setRow(b, firstFixLine);

  return result;
}
}  // namespace Quasigroup