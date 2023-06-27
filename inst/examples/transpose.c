SEXP C_transpose(SEXP x)
{
    if (!Rf_isMatrix(x) || !Rf_isReal(x))
        Rf_error("`x` must be a real matrix");

    size_t n = Rf_nrows(x);
    size_t m = Rf_ncols(x);
    const double* xp = REAL(x);

    SEXP y = PROTECT(Rf_allocMatrix(REALSXP, m, n));
    double* yp = REAL(y);
    for (size_t i=0; i<n; ++i)
        for (size_t j=0; j<m; ++j)
            yp[j+m*i] = xp[i+n*j];

    SEXP dimnames = Rf_getAttrib(x, R_DimNamesSymbol);
    if (!Rf_isNull(dimnames)) {
        SEXP tdimnames = PROTECT(Rf_allocVector(VECSXP, 2));
        SET_VECTOR_ELT(tdimnames, 0, VECTOR_ELT(dimnames, 1));
        SET_VECTOR_ELT(tdimnames, 1, VECTOR_ELT(dimnames, 0));
        Rf_setAttrib(y, R_DimNamesSymbol, tdimnames);  // set dimnames
        UNPROTECT(1);
        // dimnames may have the names attribute too (left as an exercise)
    }

    UNPROTECT(1);
    return y;
}

/* R
transpose <- function(x)
{
    if (!is.matrix(x)) x <- as.matrix(x)
    if (!is.double(x)) x[] <- as.double(x)  # preserves attributes
    .Call("C_transpose", x, PACKAGE="transpose")
}
R */
