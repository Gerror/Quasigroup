#include "ExperimentsRunner.h"

namespace Quasigroup {

    ExperimentalReport *ExperimentsRunner::run(
            int iterations,
            int objectsPerIteration,
            Experiment *experiment
    ) {
        std::vector<double> results(iterations);
        for (int i = 0; i < iterations; i++) {
            results[i] = experiment->iterate(generator, objectsPerIteration);
        }

        auto report = new ExperimentalReport(
                factory->getOrder(),
                iterations,
                objectsPerIteration,
                results
        );
        return report;
    }

    ExperimentsRunner::~ExperimentsRunner() {
        delete generator;
    }

    ExperimentsRunner::ExperimentsRunner(QuasigroupFactory *factory) : factory(factory) {
        this->generator = new QuasigroupGenerator(factory);
    }

}