# Triplet intensity T function
# 
# Author: Tuomas Rajala <tarajala@maths.jyu.fi>
###############################################################################



Tfun<-function(X, r=NULL, ...)
{
	# main calc
	res<-spatial.graph.cluster.Fun(X, r=r, funtype=4, ...)
	
	# theoretical values, 2d
	theo<-0.5*pi*(pi-3*sqrt(3)/4)*res$r^4
				 
			     
	
	# create the fv object
	T.final<-fv( data.frame(theo=theo,T=res$v/summary(X)$int^2, r=res$r),
			argu = "r",
			alim = range(res$r),
			ylab = substitute(T(r),NULL),
			desc = c("Theoretical values","T function","Parameter values"),
			valu = "T",
			fmla = ".~r",
			fname="T"
	)
	
	# add additional notes
	attr(T.final,"note") <- res$note
	
	#return
	T.final
}

