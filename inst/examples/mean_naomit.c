SEXP C_mean_naomit(SEXP x)
{
    double ret = 0.0;
    size_t k = 0;

    if (Rf_isInteger(x)) {
        const int* xp = INTEGER(x);
        size_t n = XLENGTH(x);
        for (size_t i=0; i<n; ++i)
            if (xp[i] != NA_INTEGER) {  // NOT: ISNA(xp[i])
                ret += (double)xp[i];
                k++;
            }
    }
    else if (Rf_isReal(x)) {
        const double* xp = REAL(x);
        size_t n = XLENGTH(x);
        for (size_t i=0; i<n; ++i)
            if (!ISNA(xp[i])) {  // NOT: xp[i] == NA_REAL
                ret += xp[i];
                k++;
            }
    }
    else
        Rf_error("`x` should be a numeric vector");

    return Rf_ScalarReal((k>0)?(ret/(double)k):NA_REAL);
}

/* R
mean_naomit <- function(x)
{
    if (!is.numeric(x))  # neither integer nor double
        x <- as.numeric(x)  # convert to double
    .Call("C_mean_naomit", x, PACKAGE="mean_naomit")
}
R */
