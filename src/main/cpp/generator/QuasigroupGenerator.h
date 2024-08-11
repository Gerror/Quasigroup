#ifndef QUASIGROUP_QUASIGROUPGENERATOR_H
#define QUASIGROUP_QUASIGROUPGENERATOR_H

#include <quasigroup/factory/QuasigroupFactory.h>
#include <functional>

namespace Quasigroup {

    class QuasigroupGenerator {
    private:
        QuasigroupFactory *factory;
    public:
        explicit QuasigroupGenerator(QuasigroupFactory *factory);

        Quasigroup *generate();

        Quasigroup *generate(const std::function<bool(Quasigroup *)> &condition);

        std::vector<Quasigroup *> generateVector(int count);

        std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>
        generateSet(int count);

        std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>
        generateSet(int count, const std::function<bool(Quasigroup *)> &condition);
    };

}

#endif //QUASIGROUP_QUASIGROUPGENERATOR_H
