# Connectivity function
# 
# Author: Tuomas Rajala <tarajala@maths.jyu.fi>
###############################################################################


cumconfun<-function(X, r=NULL, R=NULL, ...)
{
	# use a intensity related clustering parameter
	if(is.null(R)) R<-1/sqrt(X$n/W.area(X$window))
	
	# main calc
	res<-spatial.graph.cluster.Fun(X, r=r, funtype=2, funpars=R, ...)

	# TODO : Plims for cumconfun
	#	data(cumconfun_plims) # envelopes from Poisson 10000 simulations
	#	plims<-NULL#cumconfun_plims, not sure yet how to scale correctly
	#plims$r<-plims$r*sqrt(200/res$sum$int)
	#plims[,-2]<-plims[,-2]*res$sum$n # scale Poisson to phenomenon
	
	# for intensity scaling
	sum0<-summary(X)
	
	# create the fv object
	cc.final<-fv( data.frame(CC=res$v/(sum0$int^2), r=res$r,theo=rep(NA,length(res$r))),
			      argu = "r",
				  alim = range(res$r),
				  ylab = substitute(CC(r),NULL),
				  desc = c(paste("Cumulative Connectivity Function with R=",R,sep=""),"Parameter values","Theoretical values unknown"),
				  valu = "CC",
		  		  fmla = ".~r",
				  fname="CC"	
	    )
		
	# add clustering parameter
	attr(cc.final,"R") <- R
	
	# add additional notes
	attr(cc.final,"note") <- res$note
	
	#return
	cc.final
	
}
