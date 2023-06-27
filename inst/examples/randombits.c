SEXP C_randombits(SEXP n)
{
    if (!Rf_isInteger(n) || XLENGTH(n) != 1)
        Rf_error("`n` should be a single integer");

    int _n = INTEGER(n)[0];
    if (_n == NA_INTEGER || _n < 1)
        Rf_error("incorrect `n`");

    SEXP y = PROTECT(Rf_allocVector(INTSXP, _n));
    int* yp = INTEGER(y);

    GetRNGstate();
    for (int i=0; i<_n; ++i)
        yp[i] = (int)(unif_rand()>0.5);  // not the best way to sample bits
    PutRNGstate();

    UNPROTECT(1);

    return y;
}

/* R
randombits <- function(n)
{
    if (!is.integer(n)) n <- as.integer(n)
    .Call("C_randombits", n, PACKAGE="randombits")
}
R */
