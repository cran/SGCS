#include <R.h>
#include "Graph.h"
#include "Components.h"



extern "C" {

SEXP test_components_c(SEXP Args)
{

	Pp pp;

	Graph graph;
	Components components;
	double *par,r0=0.0, *prepR;
	int *gtype, *doDists, *toroidal,*dbg, i0=0;
	prepR=&r0;
	doDists=&i0;
	toroidal=&i0;
//start parsing the args
	Args = CDR(Args);
	dbg = INTEGER(CAR(Args)); // if debug messages
	if(*dbg) Rprintf("Parsing parameter:");

	Args = CDR(Args);
	pp.Init(CAR(Args)); // init pp

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	gtype = INTEGER(CAR(Args)); //what type of graph

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	par = REAL(CAR(Args)); //graph par


	//	void Init(Pp *pp0, double *par, double *prepR, int *doDists, int *toroidal, int *dbg );
	if(*dbg) Rprintf("Init graph...");
	graph.Init(&pp, gtype, par, prepR, doDists, doDists, toroidal, dbg);
	graph.sg_calc();
	components.calculate(&graph);
	return components.toSEXP();
}



} //extern
