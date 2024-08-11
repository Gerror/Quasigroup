#ifndef QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H
#define QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H


#include "Experiment.h"
#include <chrono>

namespace Quasigroup {

    class CheckPropertyTimeExperiment : public Experiment {
    private:
        const std::function<void(Quasigroup *)> &checkPropertyFunction;
    public:
        explicit CheckPropertyTimeExperiment(const std::function<void(Quasigroup *)> &checkPropertyFunction);

        double iterate(QuasigroupGenerator *generator, int objectsCount) override;
    };

}

#endif //QUASIGROUP_CHECKPROPERTYTIMEEXPERIMENT_H
