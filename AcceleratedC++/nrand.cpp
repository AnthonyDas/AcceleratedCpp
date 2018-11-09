#include <cstdlib> // rand(), RAND_MAX
#include <stdexcept> // domain_error

// Returns a random integer on the range [0, n), i.e. excluding n. (p.135)
template <typename T>
static T nrand(const T &n) {
	if (n <= 0 || n > RAND_MAX) {
		throw std::domain_error("nrand argument is out of range");
	}

	const T bucket_size = RAND_MAX / n;
	T r;

	do { r = rand() / bucket_size; }
	while (r >= n);

	return r;
}