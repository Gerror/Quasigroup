#ifndef QUASIGROUP_FEISTELNETWORK_H
#define QUASIGROUP_FEISTELNETWORK_H

#include "FunctionFamily.h"
#include "GeneratedObject.h"
#include "Helper.h"

namespace Quasigroup {

    /*
     * Обобщенная сеть Фейстеля
     */

    class FeistelNetwork : public FunctionFamily, public GeneratedObject {
    public:
        explicit FeistelNetwork(int k, unsigned long long int seed = 0);
    protected:
        void generate() override;
    };

}

#endif //QUASIGROUP_FEISTELNETWORK_H
