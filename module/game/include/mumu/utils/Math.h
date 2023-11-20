#pragma once

#ifndef MUMU_MATH_H
#define MUMU_MATH_H

#include "box2d/box2d.h"
#include <stdlib.h>

namespace mumu {

#define RAND_LIMIT 32767

class Math
{

  public:
    static inline float RandomFloat()
    {
        float r = (float)(rand() & (RAND_LIMIT));
        r /= RAND_LIMIT;
        r = 2.0f * r - 1.0f;
        return r;
    }

    /// Random floating point number in range [lo, hi]
    static inline float RandomFloat(float lo, float hi)
    {
        float r = (float)(rand() & (RAND_LIMIT));
        r /= RAND_LIMIT;
        r = (hi - lo) * r + lo;
        return r;
    }
};

} // namespace mumu

#endif // MUMU_MATH_H
