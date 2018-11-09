#include <iostream>
#include <vector>
#include <string>
#include "read_grammar.h"
#include "gen_sentence.cpp"

// (p.134)
int main3() {

	// Generate the sentence
	std::vector<std::string> sentence = gen_sentence(read_grammar(std::cin));

	// Write the first word if any
	std::vector<std::string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		std::cout << *it;
		++it;
	}

	// Write the rest of the words, each preceded by a space
	while (it != sentence.end()) {
		std::cout << " " << *it;
		++it;
	}

	std::cout << "Finished - please type something to quit";
	int dummy;
	std::cin >> dummy;

	return 0;
}