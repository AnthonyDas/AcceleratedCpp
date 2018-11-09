#include <vector>
#include <string>
#include <stdexcept> // logic_error
#include "read_grammar.h"
#include "nrand.cpp"

// Bool indicating whether parameter s is angle bracketed, e.g. <...>. (p.132)
bool is_bracketed(const std::string& s) {
	return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

// Appends parameter word to the result res in either of two ways:
// - If word is a normal word, word is simply appended. 
// - If word is a category, select a random rule from the category,
// append each word from selected rule to res. This may entail
// recursive expansions if selected rule contains sub categories. (p.133)
void gen_aux(const Grammar &g, const std::string &word, std::vector<std::string> &res) {

	if (!is_bracketed(word)) {
		res.push_back(word);
	}
	else {
		// Locate the rule that corresponds to word 
		Grammar::const_iterator it = g.find(word);
		if (it == g.end()) {
			throw std::logic_error("empty rule");
		}

		// Fetch the set of possible rules
		const Rule_collection& c = it->second;

		// From which we select one at random
		const Rule& r = c[nrand(c.size())];

		// Recursively expand the selected rule
		for (Rule::const_iterator i = r.begin(); i != r.end(); ++i) {
			gen_aux(g, *i, res);
		}
	}
}

// Generate a random sentence based on the grammar provided. (p.132)
std::vector<std::string> gen_sentence(const Grammar &g) {
	std::vector<std::string> res;

	gen_aux(g, "<sentence>", res);

	return res;
}

