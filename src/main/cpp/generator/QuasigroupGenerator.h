#ifndef QUASIGROUP_QUASIGROUPGENERATOR_H
#define QUASIGROUP_QUASIGROUPGENERATOR_H

#include <quasigroup/factory/QuasigroupFactory.h>
#include <functional>
#include <set>

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
        generateUnorderedSet(int count);

        std::unordered_set<Quasigroup *, Quasigroup::QuasigroupHash, Quasigroup::QuasigroupEqualHash>
        generateUnorderedSet(int count, const std::function<bool(Quasigroup *)> &condition);

        std::set<Quasigroup *, Quasigroup::QuasigroupPointerComparator>
        generateSet(int count);

        std::set<Quasigroup *, Quasigroup::QuasigroupPointerComparator>
        generateSet(int count, const std::function<bool(Quasigroup *)> &condition);
    };

}

#endif //QUASIGROUP_QUASIGROUPGENERATOR_H
