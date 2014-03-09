# Ripley's K function
# 
# Author: Tuomas Rajala <tuomas.rajala@iki.fi>
###############################################################################



Kfun<-function(X, r=NULL, ...)
{
	# main calc
	res<-spatial.graph.cluster.Fun(X, r=r, funtype=5, ...)
	
  d <- 3-1*is.null(X$z)
	# theoretical values of Poisson, 2d
	if(d == 2) theo<-pi*res$r^2
  else theo <- (4*pi*res$r^3)/3
  
	lambda <- X$n/W.area(X$window)
	
	# create the fv object
	K.final<-fv( data.frame(theo=theo, K=res$v/lambda, r=res$r),
			argu = "r",
			alim = range(res$r),
			ylab = substitute(K(r), NULL),
			desc = c("Theoretical values","K function","Parameter values"),
			valu = "K",
			fmla = ".~r",
			fname="K"
	)
	
	# add additional notes
	attr(K.final,"note") <- res$note
	
	#return
	K.final
}

