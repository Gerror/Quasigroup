#include "ExperimentalReport.h"

namespace Quasigroup {
ExperimentalReport::ExperimentalReport(const int quasigroupOrder,
                                       const uint iterations,
                                       const uint objectsPerIteration,
                                       std::vector<double> results) {
  this->quasigroupOrder = quasigroupOrder;
  this->iterations = iterations;
  this->objectsPerIteration = objectsPerIteration;
  this->results = std::move(results);
  this->fractions = std::vector<double>(iterations);

  prepareReport();
}

void ExperimentalReport::prepareReport() {
  double tmpAverage = 0;
  double tmpMin = results[0];
  double tmpMax = results[0];

  for (int i = 0; i < iterations; i++) {
    fractions[i] = results[i] / objectsPerIteration;
    if (results[i] > tmpMax) {
      tmpMax = results[i];
    }

    if (results[i] < tmpMin) {
      tmpMin = results[i];
    }

    tmpAverage += results[i];
  }

  tmpAverage /= iterations;

  this->averageResult = tmpAverage;
  this->minResult = tmpMin;
  this->maxResult = tmpMax;
  this->averageFraction = tmpAverage / objectsPerIteration;
  this->minFraction = tmpMin / objectsPerIteration;
  this->maxFraction = tmpMax / objectsPerIteration;
}

std::ostream &operator<<(std::ostream &out, const ExperimentalReport &report) {
  out << "{" << std::endl;
  out << "\t" << R"("type": "experimental_report",)" << std::endl;

  out << "\t" << "\"results\": [" << std::endl;
  for (int i = 0; i < report.results.size() - 1; i++) {
    out << "\t\t" << report.results[i] << "," << std::endl;
  }
  out << "\t\t" << report.results[report.results.size() - 1] << std::endl;
  out << "\t" << "]," << std::endl;

  out << "\t" << "\"fractions\": [" << std::endl;
  for (int i = 0; i < report.fractions.size() - 1; i++) {
    out << "\t\t" << report.fractions[i] << "," << std::endl;
  }
  out << "\t\t" << report.fractions[report.fractions.size() - 1] << std::endl;
  out << "\t" << "]," << std::endl;

  out << "\t" << R"("quasigroup_order": )" << report.quasigroupOrder << ","
      << std::endl;
  out << "\t" << R"("iterations": )" << report.iterations << "," << std::endl;
  out << "\t" << R"("objects_per_iteration": )" << report.objectsPerIteration
      << "," << std::endl;
  out << "\t" << R"("average_result": )" << report.averageResult << ","
      << std::endl;
  out << "\t" << R"("min_result": )" << report.minResult << "," << std::endl;
  out << "\t" << R"("max_result": )" << report.maxResult << "," << std::endl;
  out << "\t" << R"("average_fraction": )" << report.averageFraction << ","
      << std::endl;
  out << "\t" << R"("min_fraction": )" << report.minFraction << ","
      << std::endl;
  out << "\t" << R"("max_fraction": )" << report.maxFraction << "" << std::endl;

  out << "}" << std::endl;

  return out;
}

int ExperimentalReport::getQuasigroupOrder() const { return quasigroupOrder; }

uint ExperimentalReport::getIterations() const { return iterations; }

uint ExperimentalReport::getObjectsPerIteration() const {
  return objectsPerIteration;
}

std::vector<double> ExperimentalReport::getResults() { return results; }

double ExperimentalReport::getAverageResult() const { return averageResult; }

double ExperimentalReport::getMaxResult() const { return maxResult; }

double ExperimentalReport::getMinResult() const { return minResult; }

std::vector<double> ExperimentalReport::getFractions() { return fractions; }

double ExperimentalReport::getAverageFraction() const {
  return averageFraction;
}

double ExperimentalReport::getMaxFraction() const { return maxFraction; }

double ExperimentalReport::getMinFraction() const { return minFraction; }
}  // namespace Quasigroup