SEXP C_square1(SEXP x)
{
    // no need to call PROTECT(x), it is already in use
    if (!Rf_isReal(x)) Rf_error("`x` should be of the type 'double'");

    size_t n = XLENGTH(x);
    const double* xp = REAL(x);

    SEXP y = PROTECT(Rf_allocVector(REALSXP, n));  // won't be GC'd
    double* yp = REAL(y);

    for (size_t i=0; i<n; ++i) {
        if (ISNA(xp[i])) yp[i] = xp[i];  // NA_REAL
        else             yp[i] = xp[i]*xp[i];
    }

    UNPROTECT(1);  // pops one object from the protect stack;
        // does not trigger garbage collection, so we can return `y` now
    return y;  // R will retrieve and protect it
}

/* R
square1 <- function(x)
{
    if (!is.double(x)) x <- as.double(x)
    .Call("C_square1", x, PACKAGE="square1")
}
R */
