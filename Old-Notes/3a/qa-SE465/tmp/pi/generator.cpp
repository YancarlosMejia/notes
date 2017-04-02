#include <cstdio>
#include <iostream>
#include <string>

#include "analyzer.h"
#include "generator.h"


/**
 * Generates the output given a set of scopes and associated function
 * and function pair counts, as well as some minimum confidence and
 * support thresholds.
 */
void generateOutput(Scopes *scopes, FunctionCount *functionCount, PairedCount *pairedCount, LookupTable *lookup, const int T_SUPPORT, const double T_CONFIDENCE) {
    for (PairedCount::iterator functionPairCount = pairedCount->begin(); functionPairCount != pairedCount->end(); ++functionPairCount) {
        int support = functionPairCount->second;
        if (support < T_SUPPORT) {
            // do not process pairs without enough support
            continue;
        }

        FunctionPair functionPair = functionPairCount->first;
        double confidenceFirst = ((double)support) / (*functionCount)[functionPair.first] * 100;
        double confidenceSecond = ((double)support) / (*functionCount)[functionPair.second] * 100;
        if (confidenceFirst < T_CONFIDENCE && confidenceSecond < T_CONFIDENCE) {
            // do not process pairs without adequate confidence for at
            // least one function
            continue;
        }

        for (Scopes::iterator info = scopes->begin(); info != scopes->end(); ++info) {
            // determine whether the first and/or second functions of the
            // pair are present in this scope
            bool foundFirst = false;
            bool foundSecond = false;
            for (Functions::iterator fx = info->functions.begin(); fx != info->functions.end(); ++fx) {
                if (*fx == functionPair.first) {
                    foundFirst = true;
                } else if (*fx == functionPair.second) {
                    foundSecond = true;
                }
            }

            // print bug related to first function
            if (confidenceFirst >= T_CONFIDENCE) {
                if (foundFirst && !foundSecond) {
                    std::cout << "bug: " << (*lookup)[functionPair.first] << " in " << (*lookup)[info->caller] << ", ";
                    std::cout << "pair: (" << (*lookup)[functionPair.first] << ", " << (*lookup)[functionPair.second] << "), ";
                    printf("support: %d, confidence: %.2f%%\n", support, confidenceFirst);
                    continue;
                }
            }
            // print bug related to second function
            if (confidenceSecond >= T_CONFIDENCE) {
                if (!foundFirst && foundSecond) {
                    std::cout << "bug: " << (*lookup)[functionPair.second] << " in " << (*lookup)[info->caller] << ", ";
                    std::cout << "pair: (" << (*lookup)[functionPair.first] << ", " << (*lookup)[functionPair.second] << "), ";
                    printf("support: %d, confidence: %.2f%%\n", support, confidenceSecond);
                    continue;
                }
            }
        }
    }
}
