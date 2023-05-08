#include "rfuns.h"


/**
 * The list of functions available in R via a call to .Call():
 * Each entry is like {exported_name, pointer, number_of_arguments}.
 */
static const R_CallMethodDef cCallMethods[] = {
    {"my_r_sum", (DL_FUNC)&my_r_sum, 1},
    {NULL, NULL, 0}  /* the end of the list */
};


/**
 * Registers the list of callable functions.
 */
void R_init_cpackagedemo(DllInfo *dll)
{
   R_registerRoutines(dll, NULL, cCallMethods, NULL, NULL);
   R_useDynamicSymbols(dll, FALSE);
}
