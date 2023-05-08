#include "rfuns.h"
#include "cfuns.h"


/** wrapper around my_c_sum */
SEXP my_r_sum(SEXP x)
{
    double s;

    if (!Rf_isReal(x)) {
        /* It's the caller who is expected to prepare
         * the arguments (tedious work) */
        Rf_error("`x` should be a vector of type 'double'");
    }

    /* TODO: consider missing value (NA) checking
     * as my_c_sum doesn't do it */

    s = my_c_sum(REAL(x), LENGTH(x));

    return Rf_ScalarReal(s);
}
