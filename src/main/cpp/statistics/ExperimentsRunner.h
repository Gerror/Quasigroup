#ifndef QUASIGROUP_EXPERIMENTSRUNNER_H
#define QUASIGROUP_EXPERIMENTSRUNNER_H

#include <quasigroup/factory/QuasigroupFactory.h>
#include <generator/QuasigroupGenerator.h>
#include "ExperimentalReport.h"
#include "Experiment.h"

namespace Quasigroup {

    class ExperimentsRunner {
    private:
        QuasigroupFactory *factory;
        QuasigroupGenerator *generator;
    public:
        explicit ExperimentsRunner(QuasigroupFactory *factory);

        ~ExperimentsRunner();

        ExperimentalReport *run(int iterations, int objectsPerIteration, Experiment *experiment);
    };

}

#endif //QUASIGROUP_EXPERIMENTSRUNNER_H
