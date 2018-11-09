#include <vector>
#include <string>
#include <algorithm> // find_if(), find_if_not() C++11
#include <cctype> // isspace
#include "split.h"

// Split words within str delimited by any white space char. (p.103)
static std::vector<std::string> split(const std::string &str) {

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
