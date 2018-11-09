#ifndef GUARD_read_grammar_h
#define GUARD_read_grammar_h

#include <vector>
#include <string>
#include <map>

// (p.131)
typedef std::vector<std::string> Rule; // E.g. <location> = "on the stairs", RHS is a vector of strings
typedef std::vector<Rule> Rule_collection; // E.g. all the different <location> rules. 
typedef std::map<std::string, Rule_collection> Grammar; // E.g. Map category to all the different rules for that category.

Grammar read_grammar(std::istream &);

#endif