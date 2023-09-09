#include "JMQuasigroupFactory.h"

namespace Quasigroup {

    LatinSquareQuasigroup *JMQuasigroupFactory::createQuasigroup(int order) {
        return new JMQuasigroup(order);
    }

}