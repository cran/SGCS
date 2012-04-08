#include <R.h>
#include "Fun.h"
#include "Clustfun.h"
#include "Confun.h"
#include "Tfun.h"


extern "C" {
//	segregationFun(pp, fpar=type, graph_type=graph_type, graph_parvec=parvec, toroidal=toroidal, dbg=dbg, funtype=4, doDists=doDists, prepR=prepR)
SEXP fun_c(SEXP Args)
{

	Pp pp;
	Graph graph;
	double prepR=0.0, *fpar, *par, *parvec,R0=0.0, *pR0;
	int *gtype, *doDists, *doWeights, *toroidal, *ftype, *dbg, parn, *incl, prepG=0;
	SEXP prepGraph;
	pR0 = &R0;

//start parsing the args
	Args = CDR(Args);
	dbg = INTEGER(CAR(Args)); // if debug messages
	if(*dbg) Rprintf("Parsing parameter:");

	Args = CDR(Args);
	pp.Init(CAR(Args)); // init pp

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	fpar = REAL(CAR(Args)); // additional function parameters.

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	gtype = INTEGER(CAR(Args)); //what type of graph

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	parvec = REAL(CAR(Args)); // parvec
	parn = length(CAR(Args));

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	ftype = INTEGER(CAR(Args)); //what type of function

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	toroidal = INTEGER(CAR(Args)); // if toroidal correction

//	if(*dbg) Rprintf(".");  // REMOVED
//	Args = CDR(Args);
//	prepR = REAL(CAR(Args)); // if preprocessing R given


	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	doDists = INTEGER(CAR(Args)); // if the distances are to be precalculated and stored

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	doWeights = INTEGER(CAR(Args)); // if the correction weights for connectivity function are to be precalculated and stored
	if(*dbg) Rprintf(".");

	Args = CDR(Args);
	incl = INTEGER(CAR(Args)); // the inclusion vector

	if(*dbg) Rprintf(".");
	Args = CDR(Args);
	prepGraph = CAR(Args); // possibly precalculated graph.
	prepG = 1- INTEGER(getListElement(prepGraph,"isnull"))[0];

	if(*dbg) Rprintf("done.\n");
	par = pR0;



	//	void Init(Pp *pp0, double *par, double *prepR, int *doDists, int *toroidal, int *dbg );
	if(*dbg) Rprintf("Init graph [");
	graph.Init(&pp, gtype, par, &prepR, doDists, doWeights, toroidal, dbg);
	if(prepG)
	{
		std::vector<std::vector<int> > prepNodelist;
		VectsxpToVector(getListElement(prepGraph,"edges"), prepNodelist);
		graph.setNodelist(&prepNodelist);
		graph.par = REAL(getListElement(prepGraph,"parameters"));
	}



	//	void Init(Graph *g0, double *par0, int *parn, int *gt, int *ft, double *fpar, int *dbg0);
	if(*dbg) Rprintf("] done.\nInit fun...");
	Fun *fun;
	if(*ftype==4)
		fun = new Tfun;
	else if(*ftype==3)
		fun = new Clustfun;
	else
		fun = new Confun;

	fun->Init(&graph, parvec, &parn, gtype, ftype, fpar, incl, dbg);
	if(*dbg) Rprintf("done.\n");

	// ok let's do the calculations
	if(*dbg) Rprintf("Calculating:\n");
	fun->calculate();
	if(*dbg) Rprintf("                                                                                                          \rdone.\n");
	//phew, done. return the value-vector in SEXP
	return fun->toSEXP();
}



} //extern
