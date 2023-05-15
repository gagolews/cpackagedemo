/* the necessary header files are automatically included by `csource`. */

SEXP C_hello()
{
    Rprintf("The mill's closed. There's no more work. We're destitute.\n"
        "I'm afraid I've no choice but to sell you all "
        "for scientific experiments.\n");
    return R_NilValue;
}

/* R
# this chunk will be extracted and executed by `csource`.

hello <- function()
    invisible(.Call("C_hello", PACKAGE="helloworld"))

R */
