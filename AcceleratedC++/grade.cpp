#include <vector>
#include <stdexcept> // domain_error
#include <algorithm> // remove_copy
#include "grade.h"
#include "median.h"
#include "average.h"
#include "Student_info.h"

// Compute a student's overall grade from midterm and final exam grades
// and homework grade. (p.52)
double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


// Compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// This function does not copy its argument, because median does so for us. (p.54)
double grade(double midterm, double final, const std::vector<double> &hw) {
	if (hw.size() == 0)
		throw std::domain_error("student has done no homework");

	return grade(midterm, final, median(hw));
}

// (p.63)
double grade(const Student_info& s) {
	return grade(s.midterm, s.final, s.homework);
}


// Call correct version of grade explicitly to help compiler. (p.113)
double grade_aux(const Student_info &s) {
	try {
		return grade(s);
	}
	catch (std::domain_error) {
		return grade(s.midterm, s.final, 0);
	}
}


// Instead of using median homework score use average. (p.115)
double average_grade(const Student_info& s) {
	return grade(s.midterm, s.final, average(s.homework));
}

// Take the median of only the non-zero homework entries. (p.116)
double optimistic_median(const Student_info &s) {
	std::vector<double> nonzero;

	std::remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);

	if (nonzero.empty()) {
		return grade(s.midterm, s.final, 0);
	}
	else {
		return grade(s.midterm, s.final, median(nonzero));
	}
}