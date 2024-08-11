#ifndef QUASIGROUP_QUASIGROUPFACTORY_H
#define QUASIGROUP_QUASIGROUPFACTORY_H

#include <quasigroup/Quasigroup.h>

namespace Quasigroup {

    class QuasigroupFactory {
    public:
        virtual int getOrder() = 0;

        virtual Quasigroup *create() = 0;
    };

}

#endif //QUASIGROUP_QUASIGROUPFACTORY_H
