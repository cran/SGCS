# Connectivity function
# 
# Author: Tuomas Rajala <tarajala@maths.jyu.fi>
###############################################################################


cumconfun<-function(pp, R=NULL, ...)
{
	if(is.null(R)) R<-1/sqrt(summary(pp)$int)
	res<-art1Fun(pp=pp, funtype=2, fpar=R, ...)
	data(cumconfun_plims) # envelopes from Poisson 10000 simulations
	plims<-NULL#cumconfun_plims, not sure yet how to scale correctly
	#plims$r<-plims$r*sqrt(200/res$sum$int)
	#plims[,-2]<-plims[,-2]*res$sum$n # scale Poisson to phenomenon
	graphfcl(list(cumconfun=res$v/(res$sum$int^2), rvec=res$parvec, plims=plims, R=R, plims=plims, note="Cumulative connectivity function",note2=res$note2))
}
