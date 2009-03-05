#import <math.h>
#import <R.h>
#import <Rinternals.h>
#import <Rdefines.h>
#import <vector>
#import "Pp.h"


double getWeight(Pp *pp, int *i, int *j);
double getWeight(int *i, int *j, int *n, std::vector<double> *);
void calcWeights(Pp *, std::vector<double> *);
