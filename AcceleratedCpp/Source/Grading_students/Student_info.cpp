#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // find
#include "Student_info.h"


// (p.64)
bool compare_Student_info(const Student_info& x, const Student_info& y) {
	return x.name < y.name;
}

// Looks in s.homework to see whether any of the values stored there is 0.
bool did_all_hw(const Student_info& s) {
	return (std::find(s.homework.begin(), s.homework.end(), 0) == s.homework.end());
}

// Read homework grades from an input stream into a vector<double> (p.57)
std::istream& read_hw(std::istream& in, std::vector<double>& hw) {

	if (in) {
		// Get rid of previous contents 
		hw.clear();

		// Read homework grades
		double x;
		while (std::cin >> x) {
			hw.push_back(x);
		}

		// Clear the stream so that input will work for the next student
		in.clear();
	}
	return in;
}

// (p.62)
std::istream& read(std::istream& in, Student_info& s) {

	// Read and stroe the students name and midterm and final exam grade
	in >> s.name >> s.midterm >> s.final;

	// Read and store all the student's homework grades
	read_hw(in, s.homework);

	return in;
}
