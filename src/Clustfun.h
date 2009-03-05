/*
 *   clustering function-class
 *
 */
#include <R.h>
#include <vector>
#include "Fun.h"
#ifndef CLUSTFUN_H_
#define CLUSTFUN_H_


class Clustfun:public Fun
{
public:
	Clustfun();
	virtual ~Clustfun();
	void calculate();
};

#endif /*CLUSTFUN_H_*/
