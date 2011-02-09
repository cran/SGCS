#include <math.h>
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <vector>
#include "Pp.h"


double getWeight(Pp *pp, int *i, int *j);
double getWeight(int *i, int *j, int *n, std::vector<double> *);
void calcWeights(Pp *, std::vector<double> *);
