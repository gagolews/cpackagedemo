#include <deque>

extern "C" SEXP C_which2(SEXP x)
{
    if (!Rf_isLogical(x)) Rf_error("`x` should be of the type 'logical'");

    size_t n = XLENGTH(x), i;
    const int* xp = LOGICAL(x);

    std::deque<size_t> d;
    for (i=0; i<n; ++i)
        if (xp[i] != NA_LOGICAL && xp[i])
            d.push_back(i);

    SEXP y = PROTECT(Rf_allocVector(REALSXP, d.size()));
    double* yp = REAL(y);  // ready for long vectors
    i=0;
    for (size_t k : d)
        yp[i++] = (double)k+1;  // R uses 1-based indexing
    UNPROTECT(1);

    return y;
}

/* R
which2 <- function(x)
{
    if (!is.logical(x)) x <- as.logical(x)
    .Call("C_which2", x, PACKAGE="which2")
}
R */
