\name{SGCS-funs}
\alias{graphfcl}
\alias{art1Fun}
\alias{confun}
\alias{cumconfun}
\alias{clustfun}
\alias{clustfun_plims}
\alias{confun_plims}
\alias{cumconfun_plims}
\alias{minusID_sg}
\alias{minusID_seg}

\title{
Connectivity function, Cumulative Connectivity function and Clustering Function.
}

\description{
Statistical measures based on edges of a geometric graph structure over a given point pattern data.
  \tabular{ll}{
    Date: \tab 2009-03-04\cr
    License: \tab GPL v2 or later\cr
}
The graph structure is in this version geometric graph, meaning points \code{x} and \code{y} are connected
if ||\code{x}-\code{y}||<\code{R} for the given range parameter \code{R}. Notice that in clustering function, the \code{R} equals to 
the parameter \code{r}.

The main function is \code{art1Fun}, but the use of shortcuts \code{confun}, \code{cumconfun} and \code{clustfun} is highly
encouraged.
}

\usage{
confun(pp, R=NULL, h=NULL, ...)
cumconfun(pp, R=NULL, ...)
clustfun(pp, ...)
art1Fun(pp, r = NULL, funtype = 1, fpar = 0, toroidal = FALSE, dbg = FALSE, 
        doDists = FALSE, doWeights = FALSE, prepR = 0, relative = FALSE, 
        prepGraph = NULL, minusR = NULL, included = NULL, parvec = NULL)
}

\arguments{
\item{pp}{All: Point pattern object. \code{ppp}-objects from package \code{spatstat} are safe.}
\item{R}{confun, cumconfun: Connection radius of the graph. If NULL, R=1/sqrt(lambda).}
\item{h}{confun: Smoothing parameter in kernel-estimation. Box kernel width = 2h.}
\item{...}{Parametes for the function art1Fun:}
\item{r}{Vector of the range parameters in which to calculate the function value. 
         if NULL, a range from 0 to 1/3 of window length is used.}
\item{funtype}{(shortcuts handle) Which function to calculate. confun=1, cumconfun=2, clustfun=3.}
\item{fpar}{(shortcuts handle) Additional function parameter(s): confun fpar=c(R,h), cumconfun fpar=R.}
\item{toroidal}{Toroidal correction of rectangular window.}
\item{dbg}{Print additional messages.}
\item{doDists}{Precalculate distances for faster computation. Be aware of memory consumption O(n\^2).}
\item{doWeights}{Precalculate confun translation correction weights for faster computation. Be aware of memory consumption O(n\^2).}
\item{prepR}{Preparation distance: If >0, precalculate a graph, from which it is easier to find needed connections. Useful with 
             other graphs (in the future).}
\item{relative}{Scale the range parameter to a unit range, i.e. scale r with sqrt(pi*lambda). Good when comparing different
                phenomena in different spatial scales.}
\item{prepGraph}{An optional graph-object from spatgraphs to be used as basis for finding connections between points. Good for big datasets.}
\item{minusR}{Minus-correction parameter. Rectangular window required, NULL means no correction.}
\item{included}{Point pattern size boolean vector for inclusion of points in computation. NULL means all points.}
\item{parvec}{Same as \code{r}.}
}

\value{
 An object of class \code{graphfcl}, which can be plotted with the generic \code{plot}-command. Contains the given parameters and
 calculated function values, and an simulation based estimation of Poisson values. Note that the Poisson values (and the limits drawn
 if flag \code{limits}=TRUE) is correct only when the R=1/sqrt(lambda).
}
\author{
Tuomas Rajala\cr
University of Jyvaskyla, Finland\cr
tarajala@maths.jyu.fi
}

\references{
Rajala, Penttinen: Spatial clustering and graph feature statistics (working title).
}

\keyword{ package }
