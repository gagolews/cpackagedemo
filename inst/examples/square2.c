SEXP C_square2(SEXP x)
{
    if (!Rf_isReal(x)) Rf_error("`x` should be of the type 'double'");

    x = PROTECT(Rf_duplicate(x));  // OK; just replaces the pointer (address)

    size_t n = XLENGTH(x);
    double* xp = REAL(x);
    for (size_t i=0; i<n; ++i)
        if (!ISNA(xp[i])) xp[i] = xp[i]*xp[i];

    UNPROTECT(1);
    return x;
}

/* R
square2 <- function(x)
{
    if (!is.double(x)) x <- as.double(x)
    .Call("C_square2", x, PACKAGE="square2")
}
R */
