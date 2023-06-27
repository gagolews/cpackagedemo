#include <deque>

extern "C" SEXP C_which2(SEXP x)
{
    if (!Rf_isLogical(x)) Rf_error("`x` should be of the type 'logical'");

    size_t n = XLENGTH(x), i, k=0;
    const int* xp = LOGICAL(x);

    // precompute k, Rf_allocVector can do a longjmp
    for (i=0; i<n; ++i) if (xp[i] != NA_LOGICAL && xp[i]) k++;
    SEXP y = PROTECT(Rf_allocVector(REALSXP, k));
    double* yp = REAL(y);  // ready for long vectors

    std::deque<size_t> d;  // allocates memory
    for (i=0; i<n; ++i)
        if (xp[i] != NA_LOGICAL && xp[i])
            d.push_back(i);

    i=0;
    for (size_t e : d)
        yp[i++] = (double)e+1;  // R uses 1-based indexing

    UNPROTECT(1);
    return y;  // d's destructor will be called automatically
}

/* R
which2 <- function(x)
{
    if (!is.logical(x)) x <- as.logical(x)
    .Call("C_which2", x, PACKAGE="which2")
}
R */
