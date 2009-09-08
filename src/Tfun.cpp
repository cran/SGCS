#include "Tfun.h"

Tfun::Tfun()
{
}

Tfun::~Tfun()
{
}

void Tfun::calculate()
{
	int iter, n, i, j, k, m, valid, ti, ni;
	double  ci, value1;

	n = graph->nodelist.size();

	for(iter=parvec.size()-1 ; iter >= 0 ; iter--)
	{
		if(*dbg)printf("Tfun %i/%i: graph[",(int)parvec.size()-iter,(int)parvec.size());
		// update graph
		*graph->oldpar = *graph->par;
		graph->par = &parvec[iter];
		graph->sg_calc();

		if(*dbg)printf("] Value[ ");

		// calc index
		value1 = 0.0;
		valid = 0; // how many legit target points
		for( i=0 ;i < n ; i++ )
		if(this->included[i])
		{
			valid++;
			ti=0;
			ni=graph->nodelist.at(i).size();
			if(ni>1) // number of triangles with i as corner
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

				value1 = value1 + ti; // sum(triplets(i))
			} // end of triangle calculation

		}// end for all points
		if(valid>0) value1 = value1 / (double) valid; // mean sum(triplets(i))
		if(*dbg)printf("%f",value1);
		value.at(iter) = value1;
		if(*this->dbg)printf(" ]\n");
	}
}
//EOF
