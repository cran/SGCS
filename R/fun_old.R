## the generic function for graph based clustering summaries
##
##
##
## Tuomas Rajala <tuomas.a.rajala@jyu.fi>
## last change 060909
############################################################
#
#graphFun<-function(pp, r=NULL, funtype=1, fpar=0, toroidal=FALSE, dbg=FALSE, doDists=FALSE, doWeights=FALSE, prepR=0.0, relative=FALSE, prepGraph=NULL, minusR=NULL, included=NULL,parvec=NULL)
## funtypes:
##	1 connectivity function
##   2 cumulative connectivity function
##   3 clustering function
#
#
#{
#	if(!is.null(r)&is.null(parvec)) parvec<-r
#	graph_type<-"geometric"
#	nGRAPHS<-c("geometric")
#	if(!graph_type%in%nGRAPHS)stop("Error art1Fun: Wrong graphtype.")
#	typei<-which(graph_type==nGRAPHS)-1
#	
#	if(class(prepGraph)!="sg" & !is.null(prepGraph) )stop("Error art1Fun: Prepared graph is not of type 'sg'.") 
#	
#	if(!funtype%in%c(1,2,3))stop("Error art1Fun: wrong function type.")
#	
#	if(funtype%in%c(1,2) & toroidal)stop("Error art1Fun: Cannon do toroidal correction in addition to translation correction.")
#	
#	lambda<-pp$n/W.area(pp$window)
#	
#	note2<-""
#	
#	if(is.null(parvec))parvec<-seq(0,min(diff(pp$window$x)/3,diff(pp$window$y)/3),length=50)
#	if(relative){note2<-"r scaled with sqrt(pi*lambda)"; parvec<-parvec/sqrt(pi*lambda)}
#	
#	if(is.null(pp$z)){pp$z<-0.0*pp$x;pp$window$z<-c(0.0,1.0);}
#	
#	pp$x<-as.numeric(pp$x);pp$y<-as.numeric(pp$y);pp$z<-as.numeric(pp$z);
#	
#	pp$window$x<-as.numeric(pp$window$x);pp$window$y<-as.numeric(pp$window$y);pp$window$z<-as.numeric(pp$window$z);
#	
#	pp$marks<-included<-as.integer(rep(1,pp$n))
#	
#	prepGraph$'isnull'<- as.integer(is.null(prepGraph))
#	
#	if(!is.null(minusR)) included<-minusID_seg(pp, minusR)
#	if(is.null(included) | length(included)!=pp$n) included<-rep(1,pp$n)
#	
#	sum0<-list(int=lambda)
#	
#	res<-.External("fun_c", 
#			as.integer(dbg), 
#			pp, 
#			as.numeric(fpar), 
#			as.integer(typei), 
#			as.numeric(parvec), 
#			as.integer(funtype),
#			as.integer(toroidal),
#			as.numeric(prepR),
#			as.integer(doDists),
#			as.integer(doWeights),
#			as.integer(included),
#			prepGraph,
#			PACKAGE='SGCS')
#	list(v=res, note2=note2, parvec=parvec, minusR=minusR,funtype=funtype,fpar=fpar, sum=sum0)
#}
#
#
## quick rectangle minus-sampling
#minusID_seg<- function (pp0, minusR)
#{
#	id <- (pp0$x < (pp0$window$x[2] - minusR)) & (pp0$x > (pp0$window$x[1] +
#					minusR)) & (pp0$y < (pp0$window$y[2] - minusR)) & (pp0$y >
#				(pp0$window$y[1] + minusR))
#	id
#}
#
## calc the rect area/volume
#W.area<-function(w)
#{
#	if(is.null(w$z) )w$z<-c(0,1)
#	abs( diff(w$x)*diff(w$y)*diff(w$z))
#}