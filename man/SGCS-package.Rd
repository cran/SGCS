\name{SGCS-package}
\alias{SGCS-package}
\alias{SGCS}
\alias{clustfun_plims}
\alias{confun_plims}
\alias{cumconfun_plims}
\docType{package}

\title{
Spatial point process statistics based on a geometric graph.
}

\description{
Three statistical spatial point pattern measures, based on a graph structure over the point pattern data.

\preformatted{
Functions
------------------
confun      -  Connectivity function
cumconfun   -  Cumulative connectivity function
clustfun    -  Clustering function
Tfun        -  Triplet intensity function T
 }

The connectivity function estimates the probability that two points distance r-apart share a graph component. Cumulative 
connectivity function is like Ripley's K-function but conditioned on the points sharing a graph component. Clustering function
is a functional form of the non-spatial graph index, clustering coefficient. Tfun is the intensity of r-triplets.

The package currently supports only geometric graph, but such graphs as k-nearest neighbours graph can be easily included
 if somebody is interested.
}

\author{
Tuomas Rajala\cr
University of Jyvaskyla, Finland\cr
tuomas.rajala@iki.fi
}

\references{
Rajala, Penttinen: Spatial clustering and graph based statistical features, JYU preprints, 2010.

Schladitz, Baddeley: A Third order point process characteristic, SJS, vol 27, 657-671, 2000.
}

\keyword{ package }
