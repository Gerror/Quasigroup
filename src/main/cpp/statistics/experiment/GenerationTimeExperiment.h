#ifndef QUASIGROUP_GENERATIONTIMEEXPERIMENT_H
#define QUASIGROUP_GENERATIONTIMEEXPERIMENT_H


#include "Experiment.h"
#include <chrono>

namespace Quasigroup {

    class GenerationTimeExperiment : public Experiment {
    public:
        double iterate(QuasigroupGenerator *generator, int objectsCount) override;
    };

}

#endif //QUASIGROUP_GENERATIONTIMEEXPERIMENT_H
