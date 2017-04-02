#include <utility>

#include "analyzer.h"
#include "parser.h"

#ifdef DEBUG
    #include <iostream>
#endif


/**
 * Analyze our scopes to determine the number of times each function is
 * called and the number of times they're called together.
 */
void analyze(Scopes *scopes, FunctionCount *functionCount, PairedCount *pairedCount, LookupTable *lookup) {
    for (Scopes::iterator local = scopes->begin(); local != scopes->end(); ++local) {
        Functions processed = Functions();
        for (Functions::iterator fx = local->functions.begin(); fx != local->functions.end(); ++fx) {
            // increment count for this function
            ++(*functionCount)[*fx];

            // for each function previously analyzed in this scope...
            for (Functions::iterator oldFx = processed.begin(); oldFx != processed.end(); ++oldFx) {
                // generate a pair sorted by alphabetical order to avoid extra
                // processing later
                FunctionPair functionPair;
                if ((*lookup)[*oldFx] < (*lookup)[*fx]) {
                    functionPair = std::make_pair(*oldFx, *fx);
                } else {
                    functionPair = std::make_pair(*fx, *oldFx);
                }
                // increment count for this function pair
                ++(*pairedCount)[functionPair];
            }

            processed.insert(*fx);
        }
    }

#ifdef DEBUG
    std::cerr << "Analyzer returned:" << std::endl;
    std::cerr << "  Functions:" << std::endl;
    for (Scopes::iterator scope = scopes->begin(); scope != scopes->end(); ++scope) {
        std::cerr << "    " << (*lookup)[scope->caller] << std::endl;
        for (Functions::iterator element = scope->functions.begin(); element != scope->functions.end(); ++element) {
            std::cerr << "      " << (*lookup)[*element] << std::endl;
        }
    }
    std::cerr << "  FunctionCount:" << std::endl;
    for (FunctionCount::iterator element = functionCount->begin(); element != functionCount->end(); ++element) {
        std::cerr << "    " << (*lookup)[element->first] << " -> " << element->second << std::endl;
    }
    std::cerr << "  PairedCount:" << std::endl;
    for (PairedCount::iterator element = pairedCount->begin(); element != pairedCount->end(); ++element) {
        std::cerr << "    " << "[" << (*lookup)[element->first.first] << ", " << (*lookup)[element->first.second] << "] -> " << element->second << std::endl;
    }
#endif
}
