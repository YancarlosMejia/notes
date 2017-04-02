#include <cstdlib>

#include "analyzer.h"
#include "generator.h"
#include "parser.h"
#include "transformer.h"


int main(int argc, char *argv[]) {
    Scopes *scopes = new Scopes();
    LookupTable *lookup = new LookupTable();
    // parse call graph
    parse(argv[1], scopes, lookup);

    int transforms = atoi(argv[4]);
    for (; transforms > 0; --transforms) {
        // perform requested amount of transforms
        interprocedural_transform(scopes);
    }

    FunctionCount *functionCount = new FunctionCount();
    PairedCount *pairedCount = new PairedCount();
    // analyze function and pair calls
    analyze(scopes, functionCount, pairedCount, lookup);

    int support = atoi(argv[2]);
    double confidence = atoi(argv[3]);
    // print bugs
    generateOutput(scopes, functionCount, pairedCount, lookup, support, confidence);

    return 0;
}
