#include "GenerationTimeExperiment.h"

namespace Quasigroup {

    double GenerationTimeExperiment::iterate(QuasigroupGenerator *generator, int objectsCount) {
        double result = 0.0;

        for (int i = 0; i < objectsCount; i++) {
            auto begin = std::chrono::steady_clock::now();
            generator->generate();
            auto end = std::chrono::steady_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
            result += elapsed.count() / 1000000.0;
        }

        return result;
    }

}
