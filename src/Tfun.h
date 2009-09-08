/*
 *   Triplet T function-class
 *
 */
#include <R.h>
#include <vector>
#include "Fun.h"
#ifndef TFUN_H_
#define TFUN_H_


class Tfun:public Fun
{
public:
	Tfun();
	virtual ~Tfun();
	void calculate();
};

#endif /*TFUN_H_*/
