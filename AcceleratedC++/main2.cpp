#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // max
#include <stdexcept> // domain_error
#include <ios> // streamsize
#include <iomanip> // setprecision
#include "Student_info.h" 
#include "grade.h" 
#include "analysis.cpp"
 
int main2() {

	// Students who did and didn't do all their homework
	std::vector<Student_info> did, didnt;

	// Read the student records and partition them
	Student_info student;
	while (read(std::cin, student)) {
		if (did_all_hw(student))
			did.push_back(student);
		else 
			didnt.push_back(student);
	}

	// Verify that the analyses will show us something useful
	if (did.empty()) {
		std::cout << "No student did all the homework!" << std::endl;
		return 1;
	}
	if (didnt.empty()) {
		std::cout << "Every student did all the homework!" << std::endl;
		return 1;
	}

	// Do the analyses
	write_analysis(std::cout, "median", median_analysis, did, didnt);
	write_analysis(std::cout, "average", average_analysis, did, didnt);
	write_analysis(std::cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

	std::cout << "Finished - please type something to quit";
	int dummy;
	std::cin >> dummy;

	return 0;
}