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
	if(*dbg0)printf("intializing graph-object: ");

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

	gtype = gtype0;
	pDist = &Graph::Dist1;  // calculate anew every time
	pWeight = &Graph::Weight1;  // calculate anew every time
	if(*doDists)  // distance triangle
	{
		if(*dbg)printf("Precalculating distances...");
		calcDists(pp, pdists,toroidal);
		pDist = &Graph::Dist2;   // retrieve from distTriangle
		if(*dbg)printf("ok. ");
	}


	if(*dbg)printf("done.\n");

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
	nodelist.clear();
	for(int i=0;i<(int)nodelist_new->size();i++)
		nodelist.push_back(nodelist_new->at(i));
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
		if(*dbg)printf("Preprocessing[");
		this->sg_geometric(prepR);
		if(*dbg)printf("] ok. ");
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
	else if(*gtype==2) this->sg_gabriel();
	else if(*gtype==3) this->sg_delauney();
}

/********************************************************************************************/
void Graph::sg_geometric()
{
 Graph::sg_geometric(par);
}

void Graph::sg_geometric(double *R)
{
	if(*dbg)printf("Geometric (R=%f):",*R);
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
	if(*dbg)printf(" Ok.");
}

void Graph::sg_shrink_geometric(double *R)
{
	if(*dbg)printf("Geometric (R=%f) (shrinking):",*R);
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
	if(*dbg)printf(" Ok.");
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
		if(*dbg)printf("%i-nn: ",*k);
		double dists2_i[*pp->n], dists2_i2[*pp->n];
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
		if(*dbg)printf("%i-nn (shrinking):",(int)*par);
		double *dists2_i, *dists2_i2;
		for(i=0;i<*pp->n;i++) //for each point
		{
			node = new std::vector<int>;
			dists2_i = new double [nodelist[i].size()];
			dists2_i2 = new double [nodelist[i].size()];
			if((int)nodelist[i].size()<*k){ printf("\n preprocessing R too small, not enough neighbours (point #%i)!!\n",i+1); return;}
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
	 if(*dbg)printf(" Ok.");
}

void Graph::sg_shrink_knn()
{

	double *R0=prepR, R=1;
	prepR = &R;
	this->sg_knn();
	prepR = R0;
}

/********************************************************************************************/
void Graph::sg_gabriel()
{
	if(*dbg)printf("Gabriel:");
	int i,j,k, empty,m,l,h;
	double x0,y0,R2, d;
	std::vector<int> *node;

	if(*this->prepR == 0) // no preprocessing done, heavy looping
	  for(i=0;i<(*pp->n-1);i++)
	  {
		  for(j=i+1;j<*pp->n;j++)
		  {
			  x0 = fabs(pp->x[i]-pp->x[j])/2.0+fmin(pp->x[i],pp->x[j]);
			  y0 = fabs(pp->y[i]-pp->y[j])/2.0+fmin(pp->y[i],pp->y[j]);
			  R2 = ( pow(pp->x[i]-pp->x[j],2) + pow(pp->y[i]-pp->y[j],2) )/4.0;
			  //		brute force
			  empty = 1;
			  for(k=0;k<*pp->n;k++)
			  {
				  if(k != i)
					  if( k != j)
					  {
						  d = pow(x0-pp->x[k],2) + pow(y0-pp->y[k],2);
						  if( d<R2 )
						  {
							  empty = 0;
							  break;
						  }
					  }
			  }
			  if(empty)
			  {
				  this->nodelist[i].push_back(j+1);this->nodelist[j].push_back(i+1);
			  }
		  }
	  }
	else{ // preprocessed: nodelist has the restricted neighbourhoods to look trough
		if(*dbg)printf("(prepd): ");
		for(i = 0 ; i< *pp->n ;  i++)
		{
			node = new std::vector<int>;
			for( l=0 ; l < (int)this->nodelist[i].size(); l++ )
			{
				j = this->nodelist[i][l]-1;
				x0 = fabs(this->pp->x[i]-this->pp->x[j])/2.0+fmin(this->pp->x[i],this->pp->x[j]);
				y0 = fabs(this->pp->y[i]-this->pp->y[j])/2.0+fmin(this->pp->y[i],this->pp->y[j]);
				R2 = (pow(this->pp->x[i]-this->pp->x[j],2) + pow(this->pp->y[i]-this->pp->y[j],2) )/4.0;
				empty = 1;
				for(m=0; m < (int)this->nodelist[i].size();m++) // the small ball is included in the preprocessing ball
				{
					k = this->nodelist[i][m]-1;
					if(k != i)
						if( k != j)
						{
							d = pow(x0-pp->x[k],2) + pow(y0-pp->y[k],2);
							if( d<R2 )
							{
								empty = 0;
								break;
							}
						}
				}
				if(empty)
				{
					node->push_back(j+1);
				}
			}
			nodelist[i].clear();
			for(h=0;h<(int)node->size();h++) nodelist[i].push_back(node->at(h));
			delete node;
		}
	}
	  if(*dbg)printf(" Ok.");
}

/********************************************************************************************/
void Graph::sg_delauney()
{
//Naive algorithm, checks the interiors of triangle circumcircles.
//For 2D patterns

	if(*dbg)printf("Delauney: ");
	int i,j,k,l,h;
	double dummy[2];
	std::vector<int> *node;
	if(*this->prepR==0) // no preprocessing done, heavy looping
	{
		if(*dbg)printf("(raw):");
		for(i = 0 ; i< *pp->n-2 ; i++ )
			for(j = i+1 ; j < *pp->n-1 ; j++ )
				for(k = j+1 ; k < *pp->n ; k++ )
					if( Empty(pp->x,pp->y,pp->n,i,j,k, dummy, dummy, dummy) )
					{
						nodelist[i].push_back(j+1);nodelist[i].push_back(k+1);
						nodelist[j].push_back(i+1);nodelist[j].push_back(k+1);
						nodelist[k].push_back(i+1);nodelist[k].push_back(j+1);
					}
	}
	else{ // preprocessed: nodelist has the restricted neighbourhoods to look trough for triangles
		if(*dbg)printf("(prepd): ");
		for(i = 0 ; i< *pp->n ;  i++)
		{
			node = new std::vector<int>;
			for( l=0 ; l < (int)nodelist[i].size()-1; l++ )
			{
				j = nodelist[i][l]-1;
				for(h=l+1; h < (int)nodelist[i].size();h++ )
				{
					k = nodelist[i][h]-1;
					if( Empty(pp->x,pp->y,pp->n,i,j,k,dummy, dummy, dummy) )
					{
						node->push_back(j+1);
						node->push_back(k+1);
					}
				}
			}
			nodelist[i].clear();nodelist[i].resize(0);
			for(h=0;h< (int)node->size();h++) nodelist[i].push_back((*node).at(h));
			delete node;
		}
	}
	if(*dbg)printf(" Ok.");

}

// EOF
