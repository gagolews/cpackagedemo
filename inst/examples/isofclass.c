#include <string.h>

SEXP C_isofclass(SEXP x, SEXP class)
{
    if (!Rf_isString(class) && XLENGTH(class) != 1)
        Rf_error("`class` must be a single string");

    if (!OBJECT(x))  // is the class attribute set at all?
        return Rf_ScalarLogical(FALSE);

    SEXP xclass = Rf_getAttrib(x, R_ClassSymbol);  // STRSXP (guaranteed)
    const char* c = CHAR(STRING_ELT(class, 0));  // class arg as a C string
    size_t n = XLENGTH(xclass);
    for (size_t i=0; i<n; ++i)
        if (strcmp(CHAR(STRING_ELT(xclass, i)), c) == 0)
            return Rf_ScalarLogical(TRUE);

    return Rf_ScalarLogical(FALSE);
}

/* R
isofclass <- function(x, class)
    .Call("C_isofclass", x, class, PACKAGE="isofclass")
R */
