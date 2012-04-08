#include "Graph.h"

Graph::Graph()
{
}
/********************************************************************************************/
Graph::~Graph()
{
}
/********************************************************************************************/
double Graph::Dist1(int *i, int *j)
{
  return getDist(pp,i,j, toroidal);
}
/********************************************************************************************/
double Graph::Dist2(int *i, int *j)
{
    return getDist(i, j, pp->n, pdists);
}
/********************************************************************************************/
/********************************************************************************************/
double Graph::Weight1(int *i, int *j)
{
  return getWeight(pp,i,j);
}
/********************************************************************************************/
double Graph::Weight2(int *i, int *j)
{
    return getWeight(i, j, pp->n, pweights);
}
/********************************************************************************************/
/********************************************************************************************/
void Graph::Init(Pp *pp0, int *gtype0, double *par0, double *prepR0, int *doDists0, int *doWeights0, int *toroidal0, int *dbg0)
{
//	if(*dbg0) Rprintf("intializing graph-object: ");

	pp = pp0;
	par=par0;prepR=prepR0;
	opar = *par;
	oldpar = &opar;
	doDists=doDists0;dbg=dbg0;
	doWeights=doWeights0;
	toroidal= toroidal0;
	nodelist.resize(*pp->n);
	pdists = &distTriangle;
	pweights = &weightTriangle;
	given = 0;

	gtype = gtype0;
	pDist = &Graph::Dist1;  // calculate anew every time
	pWeight = &Graph::Weight1;  // calculate anew every time
	if(*doDists)  // distance triangle
	{
		if(*dbg) Rprintf("Precalculating distances...");
		calcDists(pp, pdists,toroidal);
		pDist = &Graph::Dist2;   // retrieve from distTriangle
		if(*dbg) Rprintf("ok. ");
	}


//	if(*dbg) Rprintf("done.\n");

}
/********************************************************************************************/
void Graph::precalculate_weights()
{
	pWeight = &Graph::Weight2;
	calcWeights(pp, pweights);
}
/********************************************************************************************/
double Graph::Dist(int *i, int *j)
{
	return (this->*pDist)(i,j);
}
/********************************************************************************************/
double Graph::Weight(int *i, int *j)
{
	return (this->*pWeight)(i,j);
}
/********************************************************************************************/
void Graph::setNodelist(std::vector<std::vector<int> > *nodelist_new)
{
	if(*dbg) Rprintf("Restoring given edges...");
	nodelist.clear();
	for(int i=0;i<(int)nodelist_new->size();i++)
		nodelist.push_back(nodelist_new->at(i));
	given = 1;
	if(*dbg) Rprintf("ok. ");
}
/********************************************************************************************/
SEXP Graph::toSEXP()
//transform a std::vector<std::vector<int> > to SEXP, desctructive
{
	SEXP graph, *node;

	PROTECT(graph = allocVector(VECSXP, this->nodelist.size()));
	int i,j, *p, n;
	for(i=0;i< (int)this->nodelist.size();i++)
	{
		node = new SEXP;
		PROTECT(*node = allocVector(INTSXP, this->nodelist[i].size()) );
		p = INTEGER(*node);
		n = this->nodelist[i].size();
		if(n<1) p[0]=NULL;
		else
			for(j=0;j<n;j++)
			{
				p[j] = (int) this->nodelist[i][j];
			};
		this->nodelist[i].clear();
		SET_VECTOR_ELT(graph, i, *node);
		UNPROTECT(1);
	}
	UNPROTECT(1);
	return graph;
}
/********************************************************************************************/
//The graph methods
/********************************************************************************************/
void Graph::sg_calc()
{
	// preprocess if requested
	if(prepR[0]>0 && *oldpar<= *par )
	{
		if(*dbg) Rprintf("Preprocessing[");
		this->sg_geometric(prepR);
		if(*dbg) Rprintf("] ok. ");
	}
	if(*gtype==0)
	{
		if(*oldpar > *par)
			this->sg_shrink_geometric(par);
		else
			this->sg_geometric();
	}
	else if(*gtype==1)
	{
		if(*oldpar > *par)
			this->sg_shrink_knn();
		else
			this->sg_knn();
	}
}

/********************************************************************************************/
void Graph::sg_geometric()
{
 Graph::sg_geometric(par);
}

void Graph::sg_geometric(double *R)
{
	if(*dbg) Rprintf("Geometric (R=%f):",*R);
	int i,j;
	double dist;
	for(i=0;i<(*pp->n-1);i++)
		for(j=i+1;j<*pp->n;j++)
		{
			dist = (this->*pDist)(&i,&j);
			if(dist<*R){
				nodelist[i].push_back(j+1);
				nodelist[j].push_back(i+1);
			}
		}
	if(*dbg) Rprintf(" Ok.");
}

void Graph::sg_shrink_geometric(double *R)
{
	if(*dbg) Rprintf("Geometric (R=%f) (shrinking):",*R);
	int i,j,j0;
	double dist;
	std::vector<int> *node;
	for(i=0; i < *pp->n ; i++)
	{
		node = new std::vector<int>;
		for(j=0;j < (int)this->nodelist[i].size() ; j++)
		{
			j0 = nodelist[i][j]-1;
			dist = (this->*pDist)(&i,&j0);
			if(dist<*R)
				node->push_back(j0+1);
		}
		nodelist[i].clear();
		for (j = 0; j < (int)node->size(); ++j) this->nodelist[i].push_back(node->at(j));
		delete node;
	}
	if(*dbg) Rprintf(" Ok.");
}
/********************************************************************************************/
void Graph::sg_knn()
{

	int i,j,l, *k,kk;
	kk = (int) par[0];
	k = &kk;
	std::vector<int> *node;

	if(*prepR==0)// if not preprocessed
	{
		if(*dbg) Rprintf("%i-nn: ",*k);
		int n = *pp->n;
		double *dists2_i, *dists2_i2;
		dists2_i = new double[n];
		dists2_i2 = new double[n];
		for(i=0;i<*pp->n;i++) //for each point
		{
			for(j=0;j<*pp->n;j++) dists2_i2[j]=dists2_i[j]= (this->*pDist)(&i,&j); //gather the distances to others
			qsort( dists2_i, *pp->n, sizeof(double),compare_doubles); // sort distances, rising
			for(j=1;j<=*k;j++) // find the k nearest
				for(l=0;l<*pp->n;l++)
					if( dists2_i[j] == dists2_i2[l] ) //with distance comparison
					{
						nodelist[i].push_back(l+1);
						break;
					}

		}
	}
	else{ //preprocessed
		if(*dbg) Rprintf("%i-nn (shrinking):",(int)*par);
		double *dists2_i, *dists2_i2;
		for(i=0;i<*pp->n;i++) //for each point
		{
			node = new std::vector<int>;
			dists2_i = new double [nodelist[i].size()];
			dists2_i2 = new double [nodelist[i].size()];
			if((int)nodelist[i].size()<*k){ Rprintf("\n preprocessing R too small, not enough neighbours (point #%i)!!\n",i+1); return;}
			for(l=	0;l< (int)nodelist[i].size();l++)
			{
				j = nodelist[i][l]-1;
				dists2_i2[l]=(this->*pDist)(&i,&j); //gather the distances to others, given preprocessing
				dists2_i[l]=dists2_i2[l];
			}
			qsort( dists2_i, nodelist[i].size() , sizeof(double),compare_doubles); // sort distances, rising
			for(j=0;j<*k;j++) // find the k nearest
				for(l=0;l<(int)nodelist[i].size();l++)
					if( dists2_i[j] == dists2_i2[l] ) //with distance comparison
					{
						node->push_back(nodelist[i][l]);
						break;
					}
			nodelist[i].clear();nodelist[i].resize(0);
			for(j=0;j < (int)node->size();j++) nodelist[i].push_back( (*node)[j] );
			delete node;
			delete[] dists2_i;
			delete[] dists2_i2;
		}
	}
	 if(*dbg) Rprintf(" Ok.");
}

void Graph::sg_shrink_knn()
{

	double *R0=prepR, R=1;
	prepR = &R;
	this->sg_knn();
	prepR = R0;
}

/********************************************************************************************/

// EOF
