#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // transform
#include <iterator> // back_inserter
#include <stdexcept> // domain_error

#include "Student_info.h" 
#include "median.h"
#include "grade.h"


// (p.112-113)
double median_analysis(const std::vector<Student_info> &students) {
	std::vector<double> grades;

	std::transform(students.begin(), students.end(), std::back_inserter(grades), grade_aux);

	return median(grades);
}

// (p.115)
double average_analysis(const std::vector<Student_info> &students) {
	std::vector<double> grades;

	std::transform(students.begin(), students.end(), std::back_inserter(grades), average_grade);

	return median(grades);
}

// Exercise left for reader.
double optimistic_median_analysis(const std::vector<Student_info> &students) {
	std::vector<double> grades;

	std::transform(students.begin(), students.end(), std::back_inserter(grades), optimistic_median);

	return median(grades);
}

// Note function pointer parameter. (p.113)
void write_analysis(std::ostream& out, const std::string& name, double analysis(const std::vector<Student_info> &),
	const std::vector<Student_info> &did, const std::vector<Student_info> &didnt) {

	out << name << ": median(did) = " << analysis(did) <<
		": median(didnt) = " << analysis(didnt) << std::endl;
}