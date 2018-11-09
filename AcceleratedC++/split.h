#ifndef GUARD_split_h
#define GUARD_split_h

#include <vector>
#include <string>

// Split words within str delimited by any white space char. (p.103)
std::vector<std::string> split(const std::string &);


// Now writing straight to an output location os.
// E.g. os = std::ostream_iterator<std::string>(cout, "\n"). (p.152)
template <typename Out>
void split(const std::string &, Out);

#endif