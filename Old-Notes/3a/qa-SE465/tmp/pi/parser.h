#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <set>
#include <string>
#include <vector>


#define NO_CALLER -1

typedef std::set<int> Functions;

struct Scope {
    int caller;
    Functions functions;

    Scope() : caller(NO_CALLER) { }
};

typedef std::vector<Scope> Scopes;
typedef std::map<int, std::string> LookupTable;

void parse(char *, Scopes *, LookupTable *);

#endif
