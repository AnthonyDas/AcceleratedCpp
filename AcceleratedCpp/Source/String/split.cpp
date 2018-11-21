#include <vector>
#include <string>
#include <algorithm> // find_if(), find_if_not() C++11
#include <cctype> // isspace
#include "split.h"


// Split words within str delimited by any white space char. (p.88)
static std::vector<std::string> split1(const std::string &str) {

	typedef std::string::size_type string_size;

	std::vector<std::string> res;

	string_size i = 0;
	while (i != str.size()) {

		// Ignore leading blanks
		while (i != str.size() && isspace(str[i]))
			++i;

		// Find end of next word
		string_size j = i;
		while (j != str.size() && !isspace(str[j]))
			++j;

		// If we found some nonwhitespace chars
		if (i != j) {
			res.push_back(str.substr(i, j - i));
		}

		i = j;
	}
	return res;
}

// Split words within str delimited by any white space char. (p.103)
static std::vector<std::string> split2(const std::string &str) {

	typedef std::string::const_iterator iter;

	std::vector<std::string> res;

	iter i = str.begin();
	while (i != str.end()) {

		// Ignore leading blanks
		i = find_if_not(i, str.end(), isspace);

		// Find end of next word
		iter j = find_if(i, str.end(), isspace);

		// Copy the characters in [i,j)
		if (i != str.end()) {
			res.push_back(std::string(i, j));
		}

		i = j;
	}
	return res;
}


// Now writing straight to an output location os.
// E.g. os = std::ostream_iterator<std::string>(cout, "\n"). (p.152)
// The expression *os denoted the current position in the container
// to which os is bound, so we assign the value std::string(i, j) to
// the element at that position. Having done the assignment, we
// increment os so that we meet the output-iterator requirements,
// and so that the next trip through the loop will assign a value
// to the next container element. 
template <typename Out>
void split(const std::string &str, Out os) {

	typedef std::string::const_iterator iter;

	iter i = str.begin();
	while (i != str.end()) {

		// Ignore leading blanks
		i = find_if_not(i, str.end(), isspace);

		// Find end of next word
		iter j = find_if(i, str.end(), isspace);

		// Copy the characters in [i,j)
		if (i != str.end()) {
			*os++ = std::string(i, j);
		}

		i = j;
	}
}
