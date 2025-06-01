#include "KepkaTransformer.h"

namespace Quasigroup {

    Quasigroup *KepkaTransformer::transform(Quasigroup *original) {
        auto result = new LatinSquareQuasigroup(*original);

        std::vector<int> full(original->getOrder());
        std::iota(std::begin(full), std::end(full), 0);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> rDistr(1, original->getOrder() - 3);

        auto r = rDistr(gen);
        if (r % 2 == 1 && original->getOrder() % 2 == 1) {
            r++;
        }

        std::vector<int> firstCycle(r);
        std::sample(full.begin(), full.end(), firstCycle.begin(), r, gen);

        std::set<int> firstCycleSet(firstCycle.begin(), firstCycle.end());
        std::set<int> secondCycleSet(full.begin(), full.end());

        for (int i : firstCycleSet) {
            secondCycleSet.erase(i);
        }

        std::vector<int> secondCycle(secondCycleSet.begin(), secondCycleSet.end());

        std::uniform_int_distribution<> bDistr(0, secondCycle.size() - 1);
        auto b = secondCycle[bDistr(gen)];

        firstCycle.push_back(b);

        std::shuffle(firstCycle.begin(), firstCycle.end(), gen);
        std::shuffle(secondCycle.begin(), secondCycle.end(), gen);

        auto firstFixLine = transmutationFromCycle(firstCycle, original->getOrder());
        auto secondFixLine = transmutationFromCycle(secondCycle, original->getOrder());

        result->setColumn(0, secondFixLine);
        result->setRow(b, firstFixLine);

        return result;
    }

}
