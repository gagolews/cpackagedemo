my_sum <- function(x)
{
    # prepare input data:
    if (!is.double(x))
        x <- as.double(x)

    # call my_c_sum_wrapper; Note the "C_" prefix (see NAMESPACE):
    s <- .Call(C_my_c_sum_wrapper, x, PACKAGE="cpackagedemo")

    # some rather random postprocessing:
    attr(s, "what") <- deparse(substitute(x))
    s
}
