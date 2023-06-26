SEXP C_test_sharedmem(SEXP x)
{
    if (!Rf_isReal(x) || XLENGTH(x) == 0)
        Rf_error("`x` should be a non-empty vector of the type 'double'");

    REAL(x)[0] = REAL(x)[0]+1;  // never do it; always make a copy;
            // the underlying array `x` may be shared by many objects

    return R_NilValue;
}

/* R
test_sharedmem <- function(x)
    invisible(.Call("C_test_sharedmem", x, PACKAGE="sharedmem"))
R */
