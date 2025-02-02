#ifndef QUASIGROUP_DIHEDRALGROUP_H
#define QUASIGROUP_DIHEDRALGROUP_H


#include <quasigroup/square/LatinSquareQuasigroup.h>

namespace Quasigroup {

    class DihedralGroup : public LatinSquareQuasigroup {
    public:
        explicit DihedralGroup(int order);
    };

}


#endif //QUASIGROUP_DIHEDRALGROUP_H
