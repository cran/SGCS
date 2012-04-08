#include "Clustfun.h"

Clustfun::Clustfun()
{
}

Clustfun::~Clustfun()
{
}

void Clustfun::calculate()
{

	int iter, n, i, j, k, m, valid, ti, ni;
	double  ci, value1;

	value1 = 0.0;
	valid = 0;
	n = graph->nodelist.size();

	if((graph->given==1) & (*graph->par < parvec.at(parvec.size()-1)))
	{
		if(*dbg) Rprintf("Warning: Given graph has edges computed at less than the requested r-range.\n");
	}

	if(*dbg) Rprintf("Clustering function:\n");
	for(iter=parvec.size()-1 ; iter >= 0 ; iter--)
	{
		if(*dbg) Rprintf("(%i/%i) graph[",(int)parvec.size()-iter,(int)parvec.size());
		// update graph
		*graph->oldpar = *graph->par;
		graph->par = &parvec[iter];
		graph->sg_calc();

		if(*dbg) Rprintf("] Value[ ");

		// calc index
		value1 = 0.0;
		valid = 0;
		for( i=0 ;i < n ; i++ )
		if(this->included[i])
		{

			ti=0;
			ni=graph->nodelist.at(i).size();
			ci=0.0;
			valid++;
			if(ni>1) // number of triangles in the vicinity of i
			{
				for(j=0; j < ni-1; j++)
					for(k=j+1; k < ni; k++)
					{
						for(m=0; m < (int)graph->nodelist.at(graph->nodelist.at(i).at(j)-1).size(); m++)
						{
							if(graph->nodelist.at(graph->nodelist.at(i).at(j)-1).at(m) == graph->nodelist.at(i).at(k))
							{
								ti++;
								break;
							}
						}
					}

				ci = (double) ti/ (0.5 * ni*(ni-1) );
				value1 = value1 + ci; // sum(c_i)
			} // end of triangle calculation

		}
		if(valid>0) value1 = value1 / (double) valid; // mean of c_i

		if(*dbg) Rprintf("%f",value1);
		value.at(iter) = value1;
		if(*this->dbg) Rprintf(" ]                   \r");
	}
}
//EOF
