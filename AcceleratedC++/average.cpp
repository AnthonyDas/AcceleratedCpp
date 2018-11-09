#include <vector>
#include <numeric> // accumulate


// (p.115)
double average(const std::vector<double> &v) {
	// NB. accumulate third arg controls return type, hence use double 0.0  and not int 0.
	return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}
