#ifndef QUASIGROUP_EXPERIMENTALREPORT_H
#define QUASIGROUP_EXPERIMENTALREPORT_H


#include <ostream>
#include <vector>

namespace Quasigroup {

    class ExperimentalReport {
    private:
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
        ExperimentalReport(int quasigroupOrder, uint iterations, uint objectsPerIteration, std::vector<double> results);

        friend std::ostream &operator<<(std::ostream &out, const ExperimentalReport &report);

        int getQuasigroupOrder();

        uint getIterations();

        uint getObjectsPerIteration();

        std::vector<double> getResults();

        double getAverageResult();

        double getMaxResult();

        double getMinResult();

        std::vector<double> getFractions();

        double getAverageFraction();

        double getMaxFraction();

        double getMinFraction();
    };
}


#endif //QUASIGROUP_EXPERIMENTALREPORT_H
