SEXP C_test_sharedmem(SEXP x)
{
    if (!Rf_isReal(x) || XLENGTH(x) == 0)
        Rf_error("`x` should be a non-empty vector of type 'double'");

    REAL(x)[0] = REAL(x)[0]+1;  /* Never do it! The underlying array `x`
                      may be shared by many objects. Always make a copy. */

    return R_NilValue;
}

/**R
test_sharedmem <- function(x)
    invisible(.Call("C_test_sharedmem", x, PACKAGE="sharedmem"))
R**/
