#include <string>
#include <algorithm> // equal()

//  (p.105)
bool is_palindrome(const std::string& s) {
	return equal(s.begin(), s.end(), s.rbegin());
}
