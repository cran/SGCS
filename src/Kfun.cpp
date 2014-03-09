#include "Kfun.h"

Kfun::Kfun()
{
}

Kfun::~Kfun()
{
}

void Kfun::calculate()
{
	int iter, n, i, j, k, m, valid, ti, ni;
	double value1;

	n = graph->nodelist.size();

	if((graph->given==1) & (*graph->par < parvec.at(parvec.size()-1)) )
	{
		if(*dbg) Rprintf("Warning: Given graph has edges computed at less than the requested r-range.\n");
	}

	if(*dbg) Rprintf("Ripley's K function:\n");
	for(iter=parvec.size()-1 ; iter >= 0 ; iter--)
	{
		if(*dbg) Rprintf("(%i/%i) graph[",(int)parvec.size()-iter,(int)parvec.size());
		// update graph
		*graph->oldpar = *graph->par;
		graph->par = &parvec[iter];
		graph->sg_calc();
    // update inclusion, in case of border correction
    this->update_inclusion();
    
		if(*dbg) Rprintf("] Value[ ");

		// calc index
		value1 = 0.0;
		valid = 0; // how many legit target points
		for( i=0 ;i < n ; i++ )
		if(this->included[i])
		{
			valid++;
			ni = graph->nodelist.at(i).size();
			value1 = value1 + ni;
		}// end for all points
		if(valid>0) value1 = value1 / (double) valid;
		if(*dbg) Rprintf("%f",value1);
		value.at(iter) = value1;
		if(*this->dbg) Rprintf("]                 \r");
	}
}
//EOF
