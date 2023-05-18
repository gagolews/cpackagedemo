#include <R_ext/Rdynload.h>
#include "rfuns.h"

/* the list of functions available in R via a call to .Call():
   each entry is like {exported_name, fun_pointer, number_of_arguments} */
static const R_CallMethodDef cCallMethods[] = {
    {"my_c_sum_wrapper", (DL_FUNC)&my_c_sum_wrapper, 1},
    {NULL, NULL, 0}  // the end of the list
};

/* registers the list of callable functions */
void R_init_cpackagedemo(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, cCallMethods, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
