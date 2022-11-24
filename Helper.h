#ifndef HELPER_H
#define HELPER_H

#include <qimage.h>
#include <cmath>

namespace cg2{
    void clamping_minus128_127(int &val);
    void clamping0_255(int &val);
}

#endif // HELPER_H
