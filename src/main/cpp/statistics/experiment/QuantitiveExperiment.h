#ifndef QUASIGROUP_QUANTITIVEEXPERIMENT_H
#define QUASIGROUP_QUANTITIVEEXPERIMENT_H


#include <functional>
#include "Experiment.h"
#include "Quasigroup.h"

namespace Quasigroup {

    class QuantitiveExperiment : public Experiment {
    private:
        const std::function<bool(Quasigroup *)> &condition;
    public:
        explicit QuantitiveExperiment(const std::function<bool(Quasigroup *)> &condition);

        double iterate(QuasigroupGenerator *generator, int objectsCount) override;
    };

}

#endif //QUASIGROUP_QUANTITIVEEXPERIMENT_H
