#include "Fun.h"

Fun::Fun()
{
}

Fun::~Fun()
{
}


void Fun::Init(Graph *g0, double *par0, int *parn, int *gt, int *ft, double *fpar0, int *included0, int *dominus0, int *dbg0)
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
  dominus = dominus0;
}

void Fun::update_inclusion() {
  int i;
  if(this->dominus) {
    for(i=0; i < *graph->pp->n ; i++) {
      if(graph->pp->bdist[i] < *this->graph->par) this->included[i] = 0;
      else this->included[i] = 1;
    }
  }
}


void Fun::update_inclusion(double R) {
  int i;
  if(this->dominus) {
    for(i=0; i < *graph->pp->n ; i++) {
      if(graph->pp->bdist[i] < R) this->included[i] = 0;
      else this->included[i] = 1;
    }
  }
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
