# the generic function for graph based clustering summaries
#
#
#
# Tuomas Rajala <tuomas.rajala@iki.fi>
# last change 170114
###########################################################

spatial.graph.cluster.Fun<-function(X, r=NULL, funtype=1, funpars=0, 
									minusRange=NULL, toroidal=FALSE,
                  useMinusCorrection=TRUE,
									doDists=FALSE, doWeights=FALSE,  
									prepGraph=NULL, dbg=FALSE)
# funtypes:
#	1 connectivity function
#   2 cumulative connectivity function
#   3 clustering function
#   4 T function
#   5 K function  

{
	# notes
	note<-NULL
	
	# init r if not given
	if(is.null(r))r<-seq(0,min(diff(X$window$x)/3,diff(X$window$y)/3),length=50)
	
	# At the moment support only geometric graph
	nGRAPHS<-c("geometric")
	graph_type<-"geometric"
	typei<-which(graph_type==nGRAPHS)-1 # correction of index for c
		
	# check that prepGraph, if one given, is of class sg from 'spatgraphs'
	if(class(prepGraph)!="sg" & !is.null(prepGraph) )stop("Prepared component defining graph is not of type 'sg'.") 
	if(!is.null(prepGraph))
	{
		note<-paste(note,"prepGraph given, type",prepGraph$gtype,", par",paste(prepGraph$parameters,collapse=","),";")
	}
	# check the given function type
	if(!funtype%in%c(1, 2, 3, 4, 5))stop("Wrong function type.")
	
	# We already do an automatic translation correction for 1&2, toroidal only for clustfun
	if(funtype%in%c(1,2) & toroidal)stop("Cannon do toroidal correction in addition to translation correction.")
	
	# add the z-coordinate if not given
	if(is.null(X$z)){X$z<-0.0*X$x+0.5; X$window$z<-c(0.0,1.0);}
	
	# TODO: need to check if these are anymore necessary
	X$x<-as.numeric(X$x);X$y<-as.numeric(X$y);X$z<-as.numeric(X$z);
	X$window$x<-as.numeric(X$window$x);X$window$y<-as.numeric(X$window$y);X$window$z<-as.numeric(X$window$z);
	
  # maybe use these for something
  X$marks <- rep(0, X$n)
	# minus-border correction: include only those further from border or all?
	X$bdist <- rep(0, X$n)
	if(useMinusCorrection)
	{
		X$bdist <- border.distances(X)
		note<-paste(note,"Minus sampling correction")
	}
	# TODO: this is going away, not used for border correction anymore.
  included<-as.integer(rep(1, X$n))
	
	# check this flag for the c-function to know we need to calc the graph
	prepGraph$'isnull'<- as.integer(is.null(prepGraph))
	
	# main c-call
	res<-.External("fun_c", 
			as.integer(dbg), 
			X,
			as.numeric(funpars), 
			as.integer(typei), 
			as.numeric(r), 
			as.integer(funtype),
			as.integer(toroidal),
			as.integer(doDists),
			as.integer(doWeights),
			as.integer(included),
      as.integer(useMinusCorrection),
			prepGraph,
			PACKAGE='SGCS')
	
	#return 
	list(v=res, r=r, note=note)
}


# minus-correction
minusID.seg<- function (X0, minusRange)
{
  stop("minusID.seg not anymore used.")
  ok <- bdist.points(X0)>minusRange
	ok
}

# compute the distances to window border
border.distances<- function(X) {
  window <- X$window
  xmin <- min(window$x)
  xmax <- max(window$x)
  ymin <- min(window$y)
  ymax <- max(window$y)
  zmin <- min(window$z)
  zmax <- max(window$z)
  x <- X$x
  y <- X$y
  z <- X$z
  result <- pmin.int(x - xmin, xmax - x, y - ymin, ymax - y, z-zmin, zmax-z)
  result
}

# calc the rect area/volume
W.area<-function(w)
{
	if(is.null(w$z) )w$z<-c(0,1)
	abs( diff(w$x)*diff(w$y)*diff(w$z))
}