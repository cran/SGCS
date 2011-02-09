/********************************************************
 *  Translation correction weight calculation functions
 *
 *
 * upper triangle matrix for weights, i=0,...,n-1, j=0,...,n-i
 * [i,j] element is in vector( n(n-1)/2) A at position
 *  A[ ( ni - i(i-1)/2 ) + j]
 *
 * Tuomas Rajala  <tuomas@sokkelo.net>
 * 190908
 *
 * ****************/

#include "weights.h"


double getWeight(Pp *pp, int *i, int *j)
{
	if(*i==*j) return (pp->xlim[1]-pp->xlim[0])*(pp->ylim[1]-pp->ylim[0])*(pp->zlim[1]-pp->zlim[0]);
	if(*i>*j) return getWeight(pp, j, i);
	return 	(
			( pp->xlim[1]-pp->xlim[0] - fabs(pp->x[*i]-pp->x[*j]) )*
			( pp->xlim[1]-pp->xlim[0] - fabs(pp->y[*i]-pp->y[*j]) )*
			( pp->xlim[1]-pp->xlim[0] - fabs(pp->z[*i]-pp->z[*j]) )
		        	);
}
/**********************************************************************************/


double getWeight(int *i, int *j, int *n, std::vector<double> *weight)
{
	if(*i==*j) return -1;
	if(*i>*j) return getWeight(j, i, n, weight);
	return weight->at( *j-*i -1 + (int)((*i)*(*n)-(*i)*(*i+1)/2) ) ;
}
/**********************************************************************************/


void calcWeights(Pp *pp, std::vector<double> *weight)
{
	int i,j, *n;
	double d;
	n = pp->n;
	for(i=0;i<*n-1;i++)
	{
		for(j=i+1;j<*n;j++)
		{
			d = getWeight(pp, &i, &j);
			weight->push_back(d);
		}
	}
}


//EOF
