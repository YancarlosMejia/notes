#include "parser.h"
#include "transformer.h"


/**
 * Perform one inter-procedural transform, expanding the scope of each
 * function.
 */
void interprocedural_transform(Scopes *scopes) {
    // for each scope...
    for (Scopes::iterator current = scopes->begin(); current != scopes->end(); ++current) {
        Functions functionsNew = Functions();
        // ...for each function this scope calls...
        for (Functions::iterator fx = current->functions.begin(); fx != current->functions.end(); ++fx) {
            // ...find that function in our list of scopes...
            for (Scopes::iterator replacement = scopes->begin(); replacement != scopes->end(); ++replacement) {
                if (replacement->caller == *fx) {
                    // ...and add that function's list of callees to this scope's
                    // list of callees.
                    functionsNew.insert(replacement->caller);
                    functionsNew.insert(replacement->functions.begin(), replacement->functions.end());
                    break;
                }
            }
        }
        current->functions = functionsNew;
    }
}
