#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "parser.h"


std::map<std::string, int> functionToID;
int functionID;

/**
 * Gets the associated ID for a function or creates a new one if
 * that function has not yet been processed.
 */
int getOrCreateID(std::string function, LookupTable *lookup) {
    if (functionToID.find(function) == functionToID.end()) {
        functionToID[function] = functionID;
        (*lookup)[functionID] = function;
        return functionID++;
    } else {
        return functionToID[function];
    }
}

/**
 * Parses a call graph into a vector of scopes. Generates a lookup table
 * to-be-used in printing so as to avoid string comparisons through the
 * program.
 */
void parse(char *filename, std::vector<Scope> *scopes, LookupTable *lookup) {
    std::ifstream callGraph;
    callGraph.open(filename);
    if (!callGraph.is_open()) {
        std::cerr << "Error: could not parse file." << std::endl;
        return;
    }

    functionID = 1;

    Scope currentScope;
    std::string currentLine;
    while (std::getline(callGraph, currentLine)) {
        if (currentLine.find("  C") != std::string::npos) {
            // function call or call to external node
            if (currentLine.find("function") != std::string::npos) {
                // function call: store the function ID in our current scope
                int start = currentLine.find_first_of("'") + 1;
                int amount = currentLine.find_last_of("'") - start;
                std::string fx = currentLine.substr(start, amount);

                currentScope.functions.insert(getOrCreateID(fx, lookup));
            }
        } else {
            int start = currentLine.find_first_of("'");
            if (start != std::string::npos) {
                // scope: save previous scope and store function ID in new scope
                ++start;
                int amount = currentLine.find_last_of("'") - start;

                if (currentScope.caller != NO_CALLER) {
                    scopes->push_back(currentScope);
                    currentScope = Scope();
                }

                std::string fx = currentLine.substr(start, amount);
                currentScope.caller = getOrCreateID(fx, lookup);
            } else {
                // null function: skip all callees
                while (currentLine.length() > 2) {
                    std::getline(callGraph, currentLine);
                }
            }
        }
    }

    // store last scope
    if (currentScope.caller != NO_CALLER) {
        scopes->push_back(currentScope);
    }

    callGraph.close();

#ifdef DEBUG
    std::cerr << "Parser returned:" << std::endl;
    for (Scopes::iterator local = scopes->begin(); local != scopes->end(); ++local) {
        std::cerr << "  " << (*lookup)[local->caller] << std::endl;
        for (Functions::iterator function = local->functions.begin(); function != local->functions.end(); ++function) {
            std::cerr << "    " << (*lookup)[*function] << std::endl;
        }
    }
#endif
}
