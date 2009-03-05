# Clustering function
# 
# Author: Tuomas Rajala <tarajala@maths.jyu.fi>
###############################################################################



clustfun<-function(pp, ...)
{
	
	res<-art1Fun(pp=pp, funtype=3, ...)
	data(clustfun_plims) # envelopes from Poisson 10000 simulations
	plims<-clustfun_plims
	plims$r<-plims$r*sqrt(200/summary(pp)$int) 
	#a<-res$sum$int*pi*plims$r^2
	#poisson<-(1-exp(-a)*(1+a))*(1-(3*sqrt(3))/(4*pi))
	graphfcl(list(clustfun=res$v, rvec=res$parvec, note="Clustering Function", plims=plims, note2=res$note2))
}

