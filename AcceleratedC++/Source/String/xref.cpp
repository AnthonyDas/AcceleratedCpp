#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "split.h"

// Generates a cross reference table that indicates where each word occurs in the input.
// Each word will be associated with the line number(s) on which it occurs.
// Note second parameter is a function ptr with a default. (p.126)
std::map<std::string, std::vector<int> > xref(std::istream &in, std::vector<std::string> find_words(const std::string &) = split) {

	std::string line;
	int line_number = 0;
	std::map<std::string, std::vector<int> > res;

	// Read the next line
	while (getline(in, line)) {
		++line_number;

		// Break the input line into words
		std::vector<std::string> words = find_words(line);

		// Remember that each word occurs on the current line
		for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); ++it) {
			res[*it].push_back(line_number);
		}
	}
	return res;
}