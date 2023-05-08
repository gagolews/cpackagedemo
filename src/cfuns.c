#include "cfuns.h"

/** computes the sum of all elements in an array x of size n */
double my_c_sum(const double* x, size_t n)
{
    double s = 0.0;
    for (size_t i=0; i<n; ++i) {
        /*
        This code does not treat potential missing values specially!
        (they are kinds of NaNs). To fix this, add:
        if (ISNA(x[i])) return NA_REAL;  // #include <R.h>
        */
        s += x[i];
    }
    return s;
}
