#include "Fun.h"

Fun::Fun()
{
}

Fun::~Fun()
{
}


void Fun::Init(Graph *g0, double *par0, int *parn, int *gt, int *ft, double *fpar0, int *included0, int *dbg0)
{
	int i;
	graph = g0;
	for(i=0;i<*parn;i++)
	{
		parvec.push_back(par0[i]);
		value.push_back(0.0);
	}
	included = included0;
	gtype = gt;
	ftype = ft;
	fpar = fpar0;
	dbg = dbg0;
}


SEXP Fun::toSEXP()
//transform a std::vector<double > to SEXP
{
	SEXP res;
	double *p;
	PROTECT(res = allocVector(REALSXP, this->value.size()));
	p = REAL(res);
	int i;
	for(i=0;i< (int)this->value.size();i++)
		p[i] = this->value.at(i);
	UNPROTECT(1);
	return res;
}
