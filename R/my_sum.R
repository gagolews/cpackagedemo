my_sum <- function(x)
{
    if (!is.double(x))
        x <- as.double(x)
    .Call("my_r_sum", x, PACKAGE="cpackagedemo")
}
