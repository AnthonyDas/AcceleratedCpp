#include <iostream>
#include <string>
#include <vector>
#include "Core.h"
#include "Student_info.h" // read_hw()
#include "grade.h"

// (p.230, virtual p.234)
double Core::grade() const {
	// Using scope operator to call ::grade() is essential.
	// Otherwise, compiler thinks we are recursively calling Core::grade().
	return ::grade(midterm, final, homework);
}

// (p.230, virtual p.236)
std::istream& Core::read(std::istream &in) {
	read_common(in);
	read_hw(in, homework);
	return in;
}

