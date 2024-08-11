#ifndef QUASIGROUP_EXPERIMENT_H
#define QUASIGROUP_EXPERIMENT_H


#include <quasigroup/factory/QuasigroupFactory.h>
#include <generator/QuasigroupGenerator.h>

namespace Quasigroup {

    class Experiment {
    public:
        virtual double iterate(QuasigroupGenerator *generator, int objectsCount) = 0;

        virtual ~Experiment() = default;;
    };

}


#endif //QUASIGROUP_EXPERIMENT_H
