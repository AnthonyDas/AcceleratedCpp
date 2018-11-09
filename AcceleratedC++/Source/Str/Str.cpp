#include <iostream> 
#include <algorithm> // copy
#include <iterator> // back_inserter
#include <cstring> // strlen
#include <cctype> // isspace
#include "Vec.cpp"


// Implementation of our own string class. (p.212)
class Str {
public: 

	typedef Vec<char>::size_type size_type;
	
private:
		
	Vec<char> data;

public:

	friend std::istream& operator>>(std::istream &i, Str &);
		
	// Default constructor - empty string
	Str() {}

	// Construct with n copies of c
	Str(const size_type &n, const char &c) : data(n, c) {}

	// Create a Str from a null-terminated array of char
	Str(const char* cp) {
		std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
	}

	template <typename In>
	Str(In b, In e) {
		std::copy(b, e, std::back_inserter(data));
	}

	// (p.218)
	Str& operator+=(const Str &s) {
		std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
		return *this;
	}

	size_type size() const { return data.size(); } // (p.216)

	char& operator[](size_type i) { return data[i]; } // (p.214)

	const char& operator[](size_type i) const { return data[i]; } // (p.214)

};

// (p.219)
Str operator+ (const Str &s, const Str &t) {
	Str r = s;
	r += t;
	return r;
}

// (p.216)
std::istream& operator>>(std::istream &is, Str &s) {
	// Obliterate existing value(s)
	s.data.clear();

	// Read and discard leading whitespace
	char c;
	while (is.get(c) && isspace(c)) {
		// Nothing to do, except testing the conditions
	}

	// If something to read, do so until next whitespace character
	if (is) {
		do { s.data.push_back(c); }
		while (is.get(c) && !isspace(c));

		// If we read whitespace, then put it back on the stream
		if (is) {
			is.unget();
		}
	}

	return is;
}

// (p.216)
std::ostream& operator<<(std::ostream &os, const Str &s) {
	for (Str::size_type i = 0; i != s.size(); ++i) {
		os << s[i];
	}
	return os;
}