#ifndef ANALYZER_H
#define ANALYZER_H

#include <map>
#include <utility>

#include "parser.h"


typedef std::map<int, int> FunctionCount;
typedef std::pair<int, int> FunctionPair;
typedef std::map<FunctionPair, int> PairedCount;

void analyze(Scopes *, FunctionCount *, PairedCount *, LookupTable *);

#endif
