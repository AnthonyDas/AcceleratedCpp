#include <vector>
#include <string>
#include <iostream>
#include "read_grammar.h"
#include "split.h"

Grammar read_grammar(std::istream &in) {
	Grammar res;
	std::string line;

	// Read the input
	while (getline(in, line)) {
		
		// Split the input into words
		std::vector<std::string> entry = split(line);

		if (!entry.empty()) {
			// Use the category to store the associated rule
			res[entry.front()].push_back(Rule(entry.begin() + 1, entry.end()));
		}
	}

	return res;
}
