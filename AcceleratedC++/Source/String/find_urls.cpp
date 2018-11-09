#include <string>
#include <vector>
#include <algorithm> // find_if


// (p.107)
bool not_url_char(char c) {
	// Characters in addition to alphanumeric that can appear in a URL
	static const std::string url_ch = "~;/?:@=&$-_.+!*'(),";

	return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}


// (p.107)
std::string::const_iterator url_end(std::string::const_iterator b, std::string::const_iterator e) {
	return find_if(b, e, not_url_char);
}


// (p.108)
std::string::const_iterator url_beg(std::string::const_iterator b, std::string::const_iterator e) {

	static const std::string sep = "://";

	typedef std::string::const_iterator iter;

	// i marks where the seperator was found
	iter i = b;

	while ((i = search(i, e, sep.begin(), sep.end())) != e) {

		// Make sure the separator isn't at the beginning or end of the line
		if (i != b && i + sep.size() != e) {

			// beg marks the beginning of the protocol-name
			iter beg = i;
			while (beg != b && isalpha(beg[-1]))
				--beg;

			// Is there at least one appropriate character before and after the separator?
			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}

		// The separator we found wasn't part of a URL; advance i past the separator
		i += sep.size();
	}
	return e;
}


/* Take a string argument  and look for instances of :// in that string.
Each time we find such an instance, look for the protocol-name that
precedes it, and the resource-name that follows it. (p.106) */
std::vector<std::string> find_urls(const std::string &s) {
	std::vector<std::string> res;

	typedef std::string::const_iterator iter;
	iter b = s.begin(), e = s.end();

	// Look through the entire input
	while (b != e) {

		// Look for one or more letters followed by ://
		b = url_beg(b, e);

		// If we found it
		if (b != e) {
			// Get the rest of the URL
			iter after = url_end(b, e);

			res.push_back(std::string(b, after));

			// Advance b and check for more URLs on this line
			b = after;
		}
	}
	return res;
}