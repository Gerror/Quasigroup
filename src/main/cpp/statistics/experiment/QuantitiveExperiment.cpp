#include "QuantitiveExperiment.h"

namespace Quasigroup {
QuantitiveExperiment::QuantitiveExperiment(

    const std::function<bool(Quasigroup *)> &condition)
    : condition(condition) {}

double QuantitiveExperiment::iterate(
    const std::vector<Quasigroup *> quasigroups) {
  int suitableInThisIteration = 0;
  for (const auto q : quasigroups) {
    suitableInThisIteration += condition(q);
    delete q;
  }

  return suitableInThisIteration;
}
}  // namespace Quasigroup