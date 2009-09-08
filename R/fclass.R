## fclass.R
## 
## function class for easy plotting
##
#
#	UPDATE: From 060909 obsolete, switched to 'fv'-class from 'spatstat'
## Author: Tuomas Rajala <tarajala@maths.jyu.fi>
################################################################################
#
#
#
#graphfcl<-function(x,...)
#{
#	class(x)<-'graphfcl'
#	x
#}
#
#print.graphfcl<-function(x,...)
#{
#	p<-paste(x$note,", range (",paste(range(x$rvec),collapse=","),") ",sep="")
#	if(!is.null(x$h))p<-paste(p,", h=",x$h)
#	if(!is.null(x$R))p<-paste(p,", R=",x$R)
#	cat(paste(p,".\n"))
#	if(x$note2!="")cat(paste("Note:",x$note2,".\n"))
#	cat(graph_based_function_explanations[[names(x)[[1]]]])
#	
#}
#
#
#plot.graphfcl<-function(x, ... , limits=FALSE)
#{
#	r<-x[['rvec']]
#	f<-x[[1]]
#	plot(r, f, ...)
#	pl<-x$plims
#	#if(length(p)<2) abline(h=p,col=2,lty=2)
#	if(!is.null(pl))
#	{
#		lines(pl$r,pl$pmean,col=2,lty=2)
#		if(limits)
#		{
#			lines(pl$r,pl$q0.975,lty=3,col=2)
#			lines(pl$r,pl$q0.005,lty=3,col=2)
#		}
#	}
#		
#
#}
#
#
##########
#graph_based_function_explanations<-list(
#		confun="$confun : connectivity function estimates\n$rvec : parameter values\n$R : the graph parameter\n$h : kernel bandwith\n",
#		clustfun="$clustfun: clustering function esimates\n$rvec : parameter values\n",
#		cumconfun="$cumconfun : cumulative connectivity function estimates\n$rvec : parameter values\n$R : the graph parameter\n"
#		)
