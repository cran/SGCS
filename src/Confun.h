#ifndef CONFUN_H_
#define CONFUN_H_

#include "Fun.h"
#include "Components.h"

class Confun:public Fun
{
public:
	Confun();
	virtual ~Confun();
	void calculate();
	double (Confun::*pK)(double *r, int *i, int *j, double *fpar);
	double K1(double *r, int *i, int *j, double *fpar);
	double K2(double *r, int *i, int *j, double *fpar);

};

#endif /*CONFUN_H_*/
