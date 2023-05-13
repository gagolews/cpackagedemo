my_sum <- function(x)
{
    # Prepare input data:
    if (!is.double(x))
        x <- as.double(x)

    # Call my_r_sum; Note the "C_" prefix (see NAMESPACE):
    s <- .Call(C_my_c_sum_wrapper, x, PACKAGE="cpackagedemo")

    # Some rather random postprocessing:
    attr(s, "what") <- deparse(substitute(x))
    s
}
