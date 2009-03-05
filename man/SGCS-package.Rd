\name{SGCS-package}
\alias{SGCS-package}
\alias{SGCS}
\alias{graph_based_function_explanations}
\alias{plot.graphfcl} 
\alias{print.graphfcl}
\docType{package}

\title{
Spatial point process statistics based on a geometric graph.
}

\description{
Three statistical spatial point pattern measures, based on a graph structure over the point pattern data.

  \tabular{ll}{
    Date: \tab 2009-03-04\cr
    License: \tab GPL v2 or later\cr
  }

\preformatted{
Functions
------------------
confun      -  Connectivity function
cumconfun   -  Cumulative connectivity function
clustfun    -  Clustering function
 }

The connectivity function estimates the probability that two points distance r-apart share a graph component. Cumulative 
connectivity function is like Ripley's K-function but conditioned on the points sharing a graph component. Clustering function
is a functional form of the non-spatial graph index, clustering coefficient. 

The package currently supports only geometric graph, but such graphs as k-nearest neighbours graph can be easily included
 if somebody is interested.
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
