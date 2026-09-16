#include "AbelianGroup.h"

#include <queue>

#include "utils/Helper.h"

namespace Quasigroup {
AbelianGroup::AbelianGroup(const int order, const unsigned long long int seed)
    : GeneratedObject(seed) {
  this->order = order;
  generate();
}

AbelianGroup::AbelianGroup(const std::vector<int> &cyclicGroupsOrders) {
  this->order = 1;
  for (const auto cyclicGroupOrder : cyclicGroupsOrders) {
    this->order *= cyclicGroupOrder;
  }

  this->cyclicGroupsOrders = cyclicGroupsOrders;
}

std::vector<int> AbelianGroup::convertElementToGroupComponents(
    int element) const {
  std::vector<int> result(cyclicGroupsOrders.size());

  for (int i = cyclicGroupsOrders.size() - 1; i >= 0; i--) {
    result[i] = element % cyclicGroupsOrders[i];
    element /= cyclicGroupsOrders[i];
  }

  return result;
}

int AbelianGroup::convertGroupComponentsToElement(
    const std::vector<int> &groupComponents) const {
  int result = 0;
  int multiplier = 1;

  for (int i = cyclicGroupsOrders.size() - 1; i >= 0; i--) {
    result += multiplier * groupComponents[i];
    multiplier *= cyclicGroupsOrders[i];
  }

  return result;
}

int AbelianGroup::getProduct(const int x, const int y) const {
  const auto xComponents = convertElementToGroupComponents(x);
  const auto yComponents = convertElementToGroupComponents(y);

  std::vector<int> productComponents(cyclicGroupsOrders.size());
  for (int i = 0; i < cyclicGroupsOrders.size(); i++) {
    productComponents[i] =
        mod(xComponents[i] + yComponents[i], cyclicGroupsOrders[i]);
  }

  return convertGroupComponentsToElement(productComponents);
}

std::vector<int> AbelianGroup::getCyclicGroupsOrders() const {
  return cyclicGroupsOrders;
}

void AbelianGroup::generate() {
  std::vector<int> orderFactorization;
  int tmpOrder = order;
  while (tmpOrder != 1) {
    for (int i = 2; i <= tmpOrder; i++) {
      if (tmpOrder % i == 0) {
        orderFactorization.push_back(i);
        tmpOrder /= i;
        break;
      }
    }
  }

  const auto permutation =
      generateRandomPermutation(orderFactorization.size(), getSeed() + 1);
  std::queue<int> newFactorizationOrder;
  for (int i = 0; i < orderFactorization.size(); i++) {
    newFactorizationOrder.push(orderFactorization[permutation[i]]);
  }

  std::vector<int> tmpCyclicGroupsOrders;
  int componentOrder = 1;
  while (!newFactorizationOrder.empty()) {
    const auto multiplier = newFactorizationOrder.front();
    newFactorizationOrder.pop();
    componentOrder *= multiplier;

    if (const auto nextStep = mersenne() % 2;
        newFactorizationOrder.empty() || nextStep == 1) {
      tmpCyclicGroupsOrders.push_back(componentOrder);
      componentOrder = 1;
    }
  }

  this->cyclicGroupsOrders = tmpCyclicGroupsOrders;
}
}  // namespace Quasigroup