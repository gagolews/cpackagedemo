# compiles a C or C++ source file using R CMD SHLIB,
# loads the resulting DLL, and executes the embedded R code
csource <- function(
    fname,
    libname=regmatches(basename(fname),
        regexpr("[^.]*(?=\\..*)", basename(fname), perl=TRUE)),
    shlibargs=character(),
    headers=paste0(
        "#include <R.h>\n",
        "#include <Rinternals.h>\n",
        "#include <Rmath.h>\n"
    ),
    R=file.path(R.home(), "bin/R")
) {
    stopifnot(file.exists(fname))
    stopifnot(is.character(libname), length(libname) == 1)
    stopifnot(is.character(shlibargs))
    stopifnot(is.character(headers))
    stopifnot(is.character(R), length(R) == 1)

    # read the source file:
    f <- paste(readLines(fname), collapse="\n")

    # set up output file names:
    tmpdir <- normalizePath(tempdir(), winslash="/")  # tempdir on Win uses \
    dynlib_ext <- .Platform[["dynlib.ext"]]
    libpath <- file.path(tmpdir, sprintf("%s%s", libname, dynlib_ext))
    cfname <- file.path(tmpdir, basename(fname))
    rfname <- sub("\\..*?$", ".R", cfname, perl=TRUE)

    # separate the /* R ... <R code> ... R */ chunk from the source file:
    rpart <- regexec("(?smi)^/\\* R\\s?(.*)R \\*/$", f, perl=TRUE)[[1]]
    rpart_start <- rpart
    rpart_len <- attr(rpart, "match.length")
    if (rpart_start[1] < 0 || rpart_len[1] < 0)
        stop("enclose R code between /* R ... and ... R */")

    rcode <- substr(f, rpart_start[2], rpart_start[2]+rpart_len[2]-1)
    cat(rcode, file=rfname, append=FALSE)

    # write the C/C++ file:
    ccode <- paste(
        headers,
        substr(f, 1, rpart_start[1]-1),
        substr(f, rpart_start[1]+rpart_len[1], nchar(f)),
        collapse="\n"
    )
    cat(ccode, file=cfname, append=FALSE)

    # prepare the "R CMD SHLIB ..." command:
    shlibargs <- c(
        "CMD", "SHLIB",
        sprintf("-o %s", libpath),
        cfname,
        shlibargs
    )

    # compile and load the DLL, run the extracted R script:
    retval <- FALSE
    oldwd <- setwd(tmpdir)
    tryCatch({
        if (libpath %in% sapply(getLoadedDLLs(), `[[`, "path"))
            dyn.unload(libpath)
        stopifnot(system2(R, shlibargs) == 0)  # 0 == success
        dyn.load(libpath)
        source(rfname)
        retval <- TRUE
    }, error=function(e) {
        cat(as.character(e), file=stderr())
    })
    setwd(oldwd)

    if (!retval) stop("error compiling file")
    invisible(TRUE)
}
