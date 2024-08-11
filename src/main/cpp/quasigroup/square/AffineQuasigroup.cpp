#include "AffineQuasigroup.h"

namespace Quasigroup {

    AffineQuasigroup::AffineQuasigroup(int order, unsigned long long int seed) : LatinSquareQuasigroup(order), GeneratedObject(seed) {
        generate();
    }

    void AffineQuasigroup::generate() {
        std::vector<int> orderFactorization;
        int tmpOrder = order;
        while (tmpOrder != 1) {
            for (int i = 2; i <= tmpOrder; i++) {
                if (tmpOrder % i == 0) {
                    orderFactorization.push_back(i);
                    tmpOrder /= i;
                    break;
                }
            }
        }

        auto permutation = generateRandomPermutation(orderFactorization.size(), getSeed() + 1);
        std::queue<int> newFactorizationOrder;
        for (int i = 0; i < orderFactorization.size(); i++) {
            newFactorizationOrder.push(orderFactorization[permutation[i]]);
        }

        std::vector<int> cyclicGroupsOrders;
        int componentOrder = 1;
        while (!newFactorizationOrder.empty()) {
            auto multiplier = newFactorizationOrder.front();
            newFactorizationOrder.pop();
            componentOrder *= multiplier;
            auto nextStep = mersenne() % 2;

            if (newFactorizationOrder.empty() || nextStep == 1) {
                cyclicGroupsOrders.push_back(componentOrder);
                componentOrder = 1;
            }
        }

        this->abelianGroup = new AbelianGroup(cyclicGroupsOrders);
        this->alpha = new AbelianGroupAutomorphism(abelianGroup, getSeed() + 2);
        this->beta = new AbelianGroupAutomorphism(abelianGroup, getSeed() + 3);
        this->c = mersenne() % order;

        for (int x = 0; x < order; x++) {
            for (int y = 0; y < order; y++) {
                latinSquare[x][y] = abelianGroup->getProduct(
                        abelianGroup->getProduct(
                            alpha->getImage(x),
                            beta->getImage(y)
                        ),
                        c
                );
            }
        }
    }

    AffineQuasigroup::~AffineQuasigroup() {
        delete alpha;
        delete beta;
        delete abelianGroup;
    }

    AbelianGroup *AffineQuasigroup::getAbelianGroup() const {
        return abelianGroup;
    }

    AbelianGroupAutomorphism *AffineQuasigroup::getAlpha() const {
        return alpha;
    }

    AbelianGroupAutomorphism *AffineQuasigroup::getBeta() const {
        return beta;
    }

    int AffineQuasigroup::getC() const {
        return c;
    }

}