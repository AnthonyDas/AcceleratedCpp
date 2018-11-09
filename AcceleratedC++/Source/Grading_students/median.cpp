// Source file for the median function (p.66)
#include <vector>
#include <algorithm> // sort()
#include <stdexcept> // domain_error
#include "median.h"

// Compute the median of a std::vector<double>.
// Note that calling this function copies the entire argument vector. (p.53, and templated p.141)
template <typename T>
T median(std::vector<T> vec) {

	typedef std::vector<T>::size_type vec_sz;

	vec_sz size = vec.size();
	if (size == 0)
		throw std::domain_error("median of an empty vector");

	std::sort(vec.begin(), vec.end());

	vec_sz mid = size / 2;

	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}