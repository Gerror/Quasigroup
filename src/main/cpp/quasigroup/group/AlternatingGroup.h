#ifndef QUASIGROUP_ALTERNATINGGROUP_H
#define QUASIGROUP_ALTERNATINGGROUP_H

#include <quasigroup/square/LatinSquareQuasigroup.h>

namespace Quasigroup {

    class AlternatingGroup : public LatinSquareQuasigroup {
    public:
        explicit AlternatingGroup(int degree);
    };

}


#endif //QUASIGROUP_ALTERNATINGGROUP_H
