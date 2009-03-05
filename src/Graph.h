#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <vector>
#include "dists.h"
#include "weights.h"
#include "Pp.h"

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph
{

public:
	Pp *pp; //the point pattern
	double *par;
	double opar;
	double *oldpar;
	int	   *doDists;
	int    *doWeights;
	int    *toroidal;
	int    *dbg;
	double *prepR;
	int    *gtype;
	std::vector<std::vector<int> > nodelist;
	std::vector<double> distTriangle;
	std::vector<double> weightTriangle;
	std::vector<double> * pdists;
	std::vector<double> * pweights;
	double (Graph::*pDist)(int*, int*);
	double Dist1(int*, int*);
	double Dist2(int*, int*);
	double Dist(int *, int *);


	double (Graph::*pWeight)(int*, int*);
	double Weight1(int*, int*);
	double Weight2(int*, int*);
	double Weight(int *, int *);
	Graph();
	virtual ~Graph();

	void Init(Pp *pp0, int *gtype0, double *par, double *prepR, int *doDists, int *doWeights, int *toroidal, int *dbg );
	void precalculate_weights();
	void setNodelist(std::vector<std::vector<int> > *nodelist_new);
	void sg_calc();
	void sg_geometric();
	void sg_geometric(double *);
	void sg_shrink_geometric(double *);
	void sg_knn();
	void sg_shrink_knn();
	void sg_gabriel();
	void sg_delauney();
	SEXP toSEXP();
};

#endif /*GRAPH_H_*/
