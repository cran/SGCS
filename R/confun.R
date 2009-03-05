# Connectivity function
# 
# Author: Tuomas Rajala <tarajala@maths.jyu.fi>
###############################################################################


confun<-function(pp, R=NULL, h=NULL, ...)
{
	if(is.null(R)) R<-1/sqrt(summary(pp)$int)
	if(is.null(h)) h<-0.15*R
	
	res<-art1Fun(pp=pp, funtype=1, fpar=c(R,h), ...)
	
	data(confun_plims) # envelopes from Poisson 10000 simulations
	plims<-confun_plims
	plims$r<-plims$r*sqrt(200/summary(pp)$int)
	graphfcl(list(confun=res$v, rvec=res$parvec, R=R, plims=plims, h=h, note="Connectivity function",note2=res$note2))
}
