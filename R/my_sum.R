my_sum <- function(x)
{
    # prepare input data:
    if (!is.double(x))
        x <- as.double(x)

    s <- .Call("my_c_sum_wrapper", x, PACKAGE="cpackagedemo")

    # some rather random postprocessing:
    attr(s, "what") <- deparse(substitute(x))
    s
}
