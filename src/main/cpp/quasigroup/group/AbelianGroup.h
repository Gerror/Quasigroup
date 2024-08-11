#ifndef QUASIGROUP_ABELIANGROUP_H
#define QUASIGROUP_ABELIANGROUP_H

#include <quasigroup/Quasigroup.h>

namespace Quasigroup {

    class AbelianGroup : public Quasigroup {
    private:
        std::vector<int> cyclicGroupsOrders;
    public:
        // if abelian group = Z_n1 x Z_n2 x ... x Z_nm
        // then cyclicGroupsOrders is array of (n1, n2, ..., nm)
        explicit AbelianGroup(std::vector<int> cyclicGroupsOrders);

        std::vector<int> getCyclicGroupsOrders() const;

        std::vector<int> convertElementToGroupComponents(int element) const;

        int convertGroupComponentsToElement(std::vector<int> groupComponents) const;

        int getProduct(int x, int y) const override;
    };

}

#endif //QUASIGROUP_ABELIANGROUP_H
