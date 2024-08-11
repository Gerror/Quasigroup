#include "JMQuasigroupFactory.h"

namespace Quasigroup {

    JMQuasigroup* JMQuasigroupFactory::create() {
        return new JMQuasigroup(order);
    }

}