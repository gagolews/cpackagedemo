SEXP C_table1(SEXP x)
{
    if (!Rf_isFactor(x)) Rf_error("`x` is not an object of class 'factor'");

    size_t n = XLENGTH(x);
    const int* xp = INTEGER(x);  // x is INTSXP

    SEXP levels = Rf_getAttrib(x, R_LevelsSymbol);  // levels is STRSXP
    size_t k = XLENGTH(levels);

    SEXP y = PROTECT(Rf_allocVector(REALSXP, k));
    double* yp = REAL(y);
    for (size_t i=0; i<k; ++i)
        yp[i] = 0.0;
    for (size_t j=0; j<n; ++j) {
        if (xp[j] != NA_INTEGER) {
            if (xp[j] < 1 || xp[j] > k)
                Rf_error("malformed factor");  // better safe than sorry
            yp[xp[j]-1]++;  // factor levels are 1..k, but C needs 0..k-1
        }
    }

    Rf_setAttrib(y, R_NamesSymbol, levels);  // set names attribute
    UNPROTECT(1);
    return y;
}

/* R
table1 <- function(x)
{
    if (!is.factor(x)) x <- as.factor(x)
    .Call("C_table1", x, PACKAGE="table1")
}
R */
