#ifndef QUASIGROUP_EXPERIMENTALREPORT_H
#define QUASIGROUP_EXPERIMENTALREPORT_H

#include <ostream>
#include <vector>

namespace Quasigroup {
class ExperimentalReport {
  int quasigroupOrder;
  uint iterations;
  uint objectsPerIteration;
  std::vector<double> results;

  double averageResult;
  double maxResult;
  double minResult;

  std::vector<double> fractions;

  double averageFraction;
  double maxFraction;
  double minFraction;

  void prepareReport();

 public:
  ExperimentalReport(int quasigroupOrder, uint iterations,
                     uint objectsPerIteration, std::vector<double> results);

  friend std::ostream &operator<<(std::ostream &out,
                                  const ExperimentalReport &report);

  int getQuasigroupOrder() const;

  uint getIterations() const;

  uint getObjectsPerIteration() const;

  std::vector<double> getResults();

  double getAverageResult() const;

  double getMaxResult() const;

  double getMinResult() const;

  std::vector<double> getFractions();

  double getAverageFraction() const;

  double getMaxFraction() const;

  double getMinFraction() const;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_EXPERIMENTALREPORT_H