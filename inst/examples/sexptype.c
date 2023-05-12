SEXP C_test_sexptype(SEXP x)
{
    Rprintf(
        "type of x: %s (SEXPTYPE=%d)\n",
        Rf_type2char(TYPEOF(x)),
        (int)TYPEOF(x)
    );
    return R_NilValue;
}


/**R

test_sexptype <- function(x)
    invisible(.Call("C_test_sexptype", x, PACKAGE="sexptype"))

R**/
