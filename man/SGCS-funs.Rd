\name{SGCS-funs}
\alias{spatial.graph.cluster.Fun}
\alias{confun}
\alias{cumconfun}
\alias{clustfun}
\alias{Tfun}
\alias{Kfun}
\alias{minusID.sg}
\alias{minusID.seg}
\alias{W.area}
\title{
Connectivity function, Cumulative Connectivity function and Clustering Function.
}

\description{
Statistical measures based on edges of a geometric graph structure over a given point pattern data.

The graph given components are used as clusters. In this version we use geometric graph, meaning points \code{x} and \code{y} are connected
if ||\code{x}-\code{y}||<\code{R} for the given range parameter \code{R}. Notice that in clustering function, the \code{R} equals to 
the parameter \code{r}. If you have a another clustering structure in mind, you can give the spatgraphs-object using the \code{prepGraph} parameter.

The main function is \code{spatial.graph.cluster.Fun}, but the use of shortcuts \code{confun}, \code{cumconfun} and \code{clustfun} is highly
encouraged.

In addition, the triplet intensity function T (Schladitz & Baddeley 2000) is also included for now: The \code{Tfun}.  
}

\usage{
confun(X, r=NULL, R=NULL, h=NULL, ...)
cumconfun(X, r=NULL, R=NULL, ...)
clustfun(X, r=NULL, ...)
Tfun(X, r=NULL, ...)
spatial.graph.cluster.Fun(X, r=NULL, funtype=1, funpars=0, 
minusRange=NULL, toroidal=FALSE,
useMinusCorrection=TRUE,
doDists=FALSE, doWeights=FALSE,  
prepGraph=NULL, dbg=FALSE)
}

\arguments{
\item{X}{All: Point pattern object of class \code{ppp} from package \code{spatstat}.}
\item{r}{Vector of the range parameters in which to calculate the function value. 
         if NULL, a range from 0 to 1/3 of window length is used.}
\item{R}{confun, cumconfun: Clustering radius of the graph. If NULL, R=1/sqrt(lambda).}
\item{h}{confun: Smoothing parameter in kernel-estimation. Box kernel width = 2h. NULL-> h=0.15*R}
\item{...}{Parametes for the function art1Fun:}
\item{funtype}{(shortcuts handle) Which function to calculate. confun=1, cumconfun=2, clustfun=3, Tfun=4.}
\item{funpars}{(shortcuts handle) Additional function parameter(s): confun fpar=c(R,h), cumconfun fpar=R.}
\item{minusRange}{clustfun, Tfun: Minus-correction parameter. Rectangular window required, NULL means no correction.}
\item{useMinusCorrection}{If true, the border correction is adaptive to range}
\item{toroidal}{clustfun, Tfun: Toroidal correction of rectangular window.}
\item{doDists}{Precalculate distances for faster computation. Be aware of memory consumption n*(n-1).}
\item{doWeights}{confun,cumconfun: Precalculate translation correction weights for faster computation. Be aware of memory consumption O(n\^2).}
\item{prepGraph}{An optional graph-object from spatgraphs to be used as the component division of the points.}
\item{dbg}{Print additional messages.}
}

\value{
Object of class \code{fv}, see \code{spatstat} for details. Has plot, envelope etc. nice methods.
}
\author{
Tuomas Rajala\cr
tuomas.rajala@iki.fi
}

\references{
Rajala, Penttinen: Spatial clustering and graph based statistical features, JYU preprints, 2010.


Schladitz, Baddeley: A Third order point process characteristic, SJS, vol 27, 657-671, 2000.
}

\examples{
set.seed(12345)
sim <- rcell(nx=15) ## the troublesome cell-model, K-function powerless
estK <- envelope(sim, r=rvec <- seq(0,0.1, length=30))
cf <- function(x, ...) clustfun(x, r=rvec)
estc <- envelope(sim, cf)
par(mfrow=c(1,2))
plot(estK)
plot(estc)
}

\keyword{ package }
