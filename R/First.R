
.onLoad <- function(lib, pkg) {
    library.dynam("SGCS", pkg, lib)
    v <- read.dcf(file=system.file("DESCRIPTION", package="SGCS"),
                  fields="Version")
    cat(paste("\nGraph based clustering summaries for point patterns,", v, "\n"))
}
