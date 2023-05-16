SEXP C_firstlast(SEXP x)
{
    if (!Rf_isVector(x) || XLENGTH(x) == 0)
        Rf_error("`x` must be a non-empty vector (atomic or generic)");
    else if (Rf_isReal(x)) {
        SEXP y = PROTECT(Rf_allocVector(REALSXP, 2));
        REAL(y)[0] = REAL(x)[0];             // first
        REAL(y)[1] = REAL(x)[XLENGTH(x)-1];  // last
        UNPROTECT(1);
        return y;
    }
    else if (Rf_isVectorList(x)) {
        SEXP y = PROTECT(Rf_allocVector(VECSXP, 2));
        // VECTOR_ELT(x, i) is PROTECTed by the container;
        // SET_VECTOR_ELT does not trigger GC, so no need to call PROTECT
        // on the result of C_firstlast(...) in this context
        SET_VECTOR_ELT(y, 0, C_firstlast(VECTOR_ELT(x, 0)));
        SET_VECTOR_ELT(y, 1, C_firstlast(VECTOR_ELT(x, XLENGTH(x)-1)));
        UNPROTECT(1);
        return y;
    }
    else
        Rf_error("other cases left as an exercise");

    return R_NilValue;  // avoid compiler warning
}

/* R
firstlast <- function(x)
    .Call("C_firstlast", x, PACKAGE="firstlast")
R */
