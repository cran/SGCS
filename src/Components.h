/*
 * Components.h
 *
 *  Created on: 19.9.2008
 *      Author: tarajala
 */
#include <vector>
#include <R.h>
#include "Graph.h"

#ifndef COMPONENTS_H_
#define COMPONENTS_H_

class Components {
public:
	Components();
	virtual ~Components();
	std::vector<std::vector<int> > componentlist;
	void calculate(Graph *graph);
	int connected(int *, int *);
	SEXP toSEXP();

};

#endif /* COMPONENTS_H_ */
