# Clustering function
# 
# Author: Tuomas Rajala <tarajala@maths.jyu.fi>
###############################################################################



clustfun<-function(X, r=NULL, ...)
{
	# main calc
	res<-spatial.graph.cluster.Fun(X, r=r, funtype=3, ...)
	
	# theoretical value depends on the mean degree:
	mdeg<-function(l,r) pi*l*r^2
	sum0<-summary(X)
	l<-sum0$int
	theo<-(1-exp(-mdeg(l,res$r))*(1+mdeg(l,res$r)))*(1-3*sqrt(3)/(4*pi))
	
	# create the fv object
	c.final<-fv( data.frame(c=res$v, r=res$r,theo=theo),
			argu = "r",
			alim = range(res$r),
			ylab = substitute(c(r),NULL),
			desc = c("Clustering function","Parameter values","Theoretical values"),
			valu = "c",
			fmla = ".~r",
			fname="c"	
	)
	
	# add additional notes
	attr(c.final,"note") <- res$note
	
	#return
	c.final
}

