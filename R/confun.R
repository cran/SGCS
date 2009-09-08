# Connectivity function
# 
# Author: Tuomas Rajala <tarajala@maths.jyu.fi>
###############################################################################


confun<-function(X, r=NULL, R=NULL, h=NULL, ...)
{
	# use a intensity related clustering parameter
	if(is.null(R)) R<-1/sqrt(X$n/W.area(X$window))
	
	# the kernel bandwidth
	if(is.null(h)) h<-0.15*R
	
	# main calc
	res<-spatial.graph.cluster.Fun(X, r=r, funtype=1, funpars=c(R,h), ...)
	
	# TODO: Theoretical values, now envelopes from Poisson 10000 simulations 
	#	data(confun_plims) # 
	#	plims<-NULL#confun_plims
	#	lambda<-pp$n/W.area(pp$window)
	#	plims$r<-plims$r*sqrt(200/lambda)
	
	C.final<-fv( data.frame(C=res$v, r=res$r,theo=rep(NA,length(res$r))),
			argu = "r",
			alim = range(res$r),
			ylab = substitute(C(r),NULL),
			desc = c(paste("Connectivity Function with R=",R,"and h=",h,sep=""),"Parameter values","Theoretical values unknown"),
			valu = "C",
			fmla = ".~r",
			fname="C"	
	)
	
	# add clustering parameter
	attr(C.final,"R") <- R
	
	# add bandwith parameter
	attr(C.final,"h") <- h
	
# add additional notes
	attr(C.final,"note") <- res$note
	
	#return
	C.final
}
