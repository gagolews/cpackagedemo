SEXP C_square(SEXP x)
{
    /* no need to call PROTECT(x), it is already in use */
    if (!Rf_isReal(x)) Rf_error("`x` should be a vector of type 'double'");

    size_t n = XLENGTH(x);
    const double* xp = REAL(x);

    SEXP y;
    PROTECT(y = Rf_allocVector(REALSXP, n));  /* won't be GC'd */
    double* yp = REAL(y);

    for (size_t i=0; i<n; ++i) {
        if (ISNA(xp[i])) yp[i] = NA_REAL;
        else             yp[i] = xp[i]*xp[i];
    }

    UNPROTECT(1);  /* pops 1 object from the protect stack;
        does not trigger garbage collection, so we can return `y` now */
    return y;
}

/* R
square <- function(x)
{
    if (!is.double(x)) x <- as.double(x)
    .Call("C_square", x, PACKAGE="square")
}
R */
