/*
 * Components.cpp
 *
 *  Created on: 19.9.2008
 *      Author: tarajala
 */

#include "Components.h"

Components::Components() {

}

Components::~Components() {

}

void Components::calculate(Graph *graph)
{
	int n, h, i, j, k, l, g, isnew, loop, sizei, sizeg, d, x;
	n = graph->nodelist.size();

	std::vector<std::vector<int> > complist;
	complist.resize(n);

	if(*graph->dbg)printf("grouping, ");
	for(i=0; i < n; i++)
	{
		complist.at(i).clear();
		for(j=0; j < (int)graph->nodelist.at(i).size(); j++)
		{

			complist.at(i).push_back( graph->nodelist.at(i).at(j)-1 );
		}
	}

	loop=1;
	d=0;
	if(*graph->dbg)printf("sorting, ");
	i=0;
	while(loop)
	{
		sizei = complist.at(i).size();

		if(sizei - d > 0 ) //unvisited neigh's left
		{
			for(k=d; k < sizei; k++ )
			{
				g = complist.at(i).at(k);
				sizeg = complist.at(g).size();
				for(j = sizeg-1; j>=0; j--) //start union of c(i) U c(g) => c(i)
				{
					isnew=1;
					h = complist.at(g).at(j);//from rear, for .pop_back()
					if( h != i)
					{
						for(l = 0; l< (int)complist.at(i).size(); l++) //is it new?
						{

							if(complist.at(i).at(l) == h) isnew=0;
						}
						if(isnew > 0)
							complist.at(i).push_back(h);
					}
					complist.at(g).pop_back();
				}// end of union
				complist.at(g).clear();
				d++;
			}
		}
		else // all neigh's of neighs i collected to c(i)
		{
			d=0;
			complist.at(i).push_back(i);
			i++;
		}
		if(i>=n)loop=0;
	}; // eo clustering loop

	std::vector<int>  *p;

	componentlist.clear();

	if(*graph->dbg)printf("cleaning");
	x=0;
	for(i=0; i< n ; i++)
	{
		p = new std::vector<int>;
		p->resize(0);
		if(complist.at(i).size()>0)
		{
			x++;
			for(j=0; j < (int)complist.at(i).size(); j++)
			{
				p->push_back(complist.at(i).at(j)+1);
				complist.at(complist.at(i).at(j)).clear();

			}
			componentlist.push_back(*p);
		}
//		delete p;
	}
	if(*graph->dbg)printf(" (x=%i)ok ",x);
}


int Components::connected(int *i, int *j)
{
	int k,l,m;
	//for(k=0; k < (int)connections.at(*i).size(); k++)
	//	if( connections.at(*i).at(k) == *j+1) return 1;
	for(k = 0; k < (int) componentlist.size(); k++)
	{
		for(l=0; l < (int) componentlist.at(k).size();l++)
			if( componentlist.at(k).at(l)== (*i+1) )
				for (m = 0; m < (int)componentlist.at(k).size(); ++m)
				{
					if(componentlist.at(k).at(m) == (*j+1))	{return 1;}
				}
	}
	return 0;
}


/********************************************************************************************/
SEXP Components::toSEXP()
//transform a std::vector<std::vector<int> > to SEXP, desctructive
{
	SEXP comps, *node;

	PROTECT(comps = allocVector(VECSXP, this->componentlist.size()));
	int i,j, *p, n;
	for(i=0;i< (int)this->componentlist.size();i++)
	{
		node = new SEXP;
		PROTECT(*node = allocVector(INTSXP, this->componentlist.at(i).size()) );
		p = INTEGER(*node);
		n = this->componentlist.at(i).size();
		if(n<1) p[0]=NULL;
		else
			for(j=0;j<n;j++)
			{
				p[j] = (int) this->componentlist.at(i).at(j);
			};
		this->componentlist.at(i).clear();
		SET_VECTOR_ELT(comps, i, *node);
		UNPROTECT(1);
	}
	UNPROTECT(1);
	return comps;
}
