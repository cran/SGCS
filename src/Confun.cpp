#include "Confun.h"

Confun::Confun()
{
}

Confun::~Confun()
{
}

double Confun::K1(double *r, int *i, int *j, double *fpar)
//box kernel estimation => connectivity function
{
	double value=0.0,d;
    d = fabs(*r - graph->Dist(i,j));
	if(d<fpar[1]) value=1.0/(2.0*fpar[1]);
	return value;
}

double Confun::K2(double *r, int *i, int *j, double *fpar)
// simple indicator 1(d<r) => cumulative connectivity function
{
	if(graph->Dist(i,j)<=*r) return(1.0);
	return(0.0);
}


void Confun::calculate()
{
	int i, j, iter, n, rn, okpairs;
	double w, k , alaosa, ylaosa;


	if(*ftype==1)
		 pK = &Confun::K1;
	if(*ftype==2)
		 pK = &Confun::K2;

	if(*dbg)
	{
		if(*ftype==1)printf("Connectivity function, R=%f, h=%f:\ngraph[",fpar[0],fpar[1]);
		else printf("Cumulative connectivity function, R=%f:\ngraph[",fpar[0]);
	}

	Components components; // start determining the pathwise connections, x~y

	// calc the graph
	*graph->par = fpar[0];
	*graph->oldpar = *graph->par;

	graph->sg_calc();
	if(*dbg)printf("] components[");
	components.calculate(graph);
	if(*graph->doWeights)
	{
		if(*dbg)printf("] weights[");
			graph->precalculate_weights();
	}

	if(*dbg)printf("] values:\n");

	n=graph->nodelist.size();
	rn = (int)parvec.size();
	for(iter=0; iter < rn; iter++)
	{
		alaosa=0.0;
		ylaosa=0.0;
		okpairs = 0;
		for( i=0 ; i<(n-1) ; i++ )
		{
			if(this->included[i])
			for( j=i+1 ; j<n ; j++ )
			{
				w = graph->Weight(&i,&j);
				if(w>0)
				{
					k = (this->*pK)(&parvec.at(iter), &i,&j, fpar);
					ylaosa = ylaosa + components.connected(&i,&j)*k/w;
				    alaosa = alaosa + k/w;
				    okpairs++;
				}
			}
		}
		if(*ftype==2) alaosa=0.5;
		value.at(iter)=ylaosa/alaosa;
		if(*dbg) printf("\r %i/%i  ",iter+1,rn);
	}
	if(*dbg) printf("\n");
}


/////////////////////////////////////////////////////////////////////////////////////
//



//EOF
