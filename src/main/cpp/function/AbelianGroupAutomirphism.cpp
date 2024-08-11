#include "AbelianGroupAutomorphism.h"

namespace Quasigroup {


    AbelianGroupAutomorphism::AbelianGroupAutomorphism(AbelianGroup *group, unsigned long long int seed)
            : GeneratedObject(seed) {
        this->group = group;
        generate();
    }

    void AbelianGroupAutomorphism::generate() {
        std::vector<int> generatingSetImages(group->getCyclicGroupsOrders().size());
        int i = 0;
        for (auto componentOrder : group->getCyclicGroupsOrders()) {
            std::vector<int> variants;
            for (int j = 1; j < componentOrder; j++) {
                auto gcd = std::gcd(j, componentOrder);
                if (gcd == 1) {
                    variants.push_back(j);
                }
            }
            int eImage = variants[mersenne() % variants.size()];
            generatingSetImages[i] = eImage;
            i++;
        }

        for (int x = 0; x < group->getOrder(); x++) {
            auto xComponents = group->convertElementToGroupComponents(x);
            for (int j = 0; j < xComponents.size(); j++) {
                xComponents[j] = mod(xComponents[j] * generatingSetImages[j], group->getCyclicGroupsOrders()[j]);
            }
            images.push_back(group->convertGroupComponentsToElement(xComponents));
        }
    }

    int AbelianGroupAutomorphism::getImage(int x) const {
        return images[x];
    }

    bool AbelianGroupAutomorphism::isCorrectHomomorphism() const {
        for (int x = 0; x < group->getOrder(); x++) {
            for (int y = 0; y < group->getOrder(); y++) {
                if (getImage(group->getProduct(x, y)) != group->getProduct(getImage(x), getImage(y))) {
                    return false;
                }
            }
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &out, const AbelianGroupAutomorphism &a) {
        for (auto x : a.images) {
            out << x << " ";
        }
        out << std::endl;
        return out;
    }

}