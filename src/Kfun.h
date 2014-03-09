/*
 *   Ripley's K function-class
 *
 */
#include <R.h>
#include <vector>
#include "Fun.h"
#ifndef KFUN_H_
#define KFUN_H_


class Kfun:public Fun
{
public:
	Kfun();
	virtual ~Kfun();
	void calculate();
};

#endif /*TFUN_H_*/
