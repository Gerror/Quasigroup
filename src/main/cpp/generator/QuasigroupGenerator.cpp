#include "LatinSquareQuasigroup.h"
#include "QuasigroupGenerator.h"

namespace Quasigroup {

    QuasigroupGenerator::QuasigroupGenerator(QuasigroupFactory *factory) {
        this->factory = factory;
    }

    Quasigroup *QuasigroupGenerator::generate() {
        return factory->create();
    }

    Quasigroup *QuasigroupGenerator::generate(const std::function<bool(Quasigroup *)> &condition) {
        while (true) {
            auto q = factory->create();
            if (condition(q)) {
                return q;
            } else {
                delete q;
            }
        }
    }

    std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>
    QuasigroupGenerator::generateSet(int count) {
        return generateSet(count, [](Quasigroup *q) { return true; });
    }

    std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>
    QuasigroupGenerator::generateSet(int count, const std::function<bool(Quasigroup *)> &condition) {
        std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash> result;
        int sizeBefore, sizeAfter;

        while (result.size() != count) {
            auto q = generate(condition);

            sizeBefore = result.size();
            result.insert(q);
            sizeAfter = result.size();

            if (sizeAfter == sizeBefore) {
                delete q;
            }
        }

        return result;
    }

    std::vector<Quasigroup *> QuasigroupGenerator::generateVector(int count) {
        std::vector<Quasigroup *> result(count);
        for (int i = 0; i < count; ++i) {
            result[i] = generate();
        }

        return result;
    }

}