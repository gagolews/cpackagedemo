SEXP C_which1(SEXP x)
{
    if (!Rf_isLogical(x)) Rf_error("`x` should be of the type 'logical'");

    size_t n = XLENGTH(x), i, k;
    const int* xp = LOGICAL(x);

    size_t* d = (size_t*)malloc(n*sizeof(size_t));  // conservative size
    if (!d) Rf_error("memory allocation error");

    for (i=0, k=0; i<n; ++i)
        if (xp[i] != NA_LOGICAL && xp[i])
            d[k++] = i;

    // Rf_allocVector can longjmp, memory leak possible...
    SEXP y = PROTECT(Rf_allocVector(REALSXP, k));
    double* yp = REAL(y);  // yes, the type is double; ready for long vectors
    for (i=0; i<k; ++i)
        yp[i] = (double)d[i]+1;  // R uses 1-based indexing

    free(d);
    UNPROTECT(1);
    return y;
}

/* R
which1 <- function(x)
{
    if (!is.logical(x)) x <- as.logical(x)
    .Call("C_which1", x, PACKAGE="which1")
}
R */
