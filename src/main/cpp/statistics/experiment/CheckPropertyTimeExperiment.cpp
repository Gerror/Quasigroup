#include "CheckPropertyTimeExperiment.h"

namespace Quasigroup {

    CheckPropertyTimeExperiment::CheckPropertyTimeExperiment(
            const std::function<void(Quasigroup *)> &checkPropertyFunction
    ) : checkPropertyFunction(checkPropertyFunction) {}

    double CheckPropertyTimeExperiment::iterate(QuasigroupGenerator *generator, int objectsCount) {
        double result = 0.0;

        for (int i = 0; i < objectsCount; i++) {
            auto q = generator->generate();

            auto begin = std::chrono::steady_clock::now();
            checkPropertyFunction(q);
            auto end = std::chrono::steady_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
            result += elapsed.count() / 1000000.0;
        }

        return result;
    }

}