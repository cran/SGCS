/* Functional class for the graph based clustering summaries
 * ftype=
 *        1   connectivity function
 *        2   cumulative connectivity function
 *        3   clustering function
 *        4
 *
 * Supports Geometric graph and toroidal correction
 * TODO: k-nn graph, border correction
 * by: Tuomas Rajala
 *
 * 	180908
 *
 */
#include <R.h>
#include <vector>
#include "Graph.h"
#ifndef FUN_H_
#define FUN_H_


class Fun
{
public:
	Graph *graph;
	std::vector<double> value;
	std::vector<double> parvec;
	int *gtype; // atm only 0 = geometric
	int *ftype;
	int *included;
	double *fpar;
	int *dbg;
	Fun();
	virtual ~Fun();
	void Init(Graph *g0, double *par0, int *parn, int *gt, int *ft, double *fpar, int *included0, int *dbg0);
	SEXP toSEXP();
	virtual	void calculate(){};
	virtual void calculateC(){};
	virtual void calculateCC(){};
	virtual void calculateT(){};
};

#endif /*FUN_H_*/
