#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // max
#include <stdexcept> // domain_error
#include <ios> // streamsize
#include <iomanip> // setprecision
#include "Student_info.h" 
#include "grade.h" 

#include "main2.cpp" 
#include "main3.cpp" 
#include "main4.cpp" 
#include "main5.cpp" 

int main() {
	// So that they get included by compiler/error checker
	main2();
	main3();
	main4();
	main5();

	std::vector<Student_info> students;
	Student_info record;
	std::string::size_type maxlen = 0; // Length of longest name

	while (read(std::cin, record)) {
		// Find length of longest name
		maxlen = std::max(maxlen, record.name.size());
		students.push_back(record);
	}

	// Sort the student records by name
	sort(students.begin(), students.end(), compare_Student_info);

	// Write the names and grades
	for (std::vector<Student_info>::size_type i = 0; i != students.size(); ++i) {

		// Write the name, padded on the right to maxlen + 1 characters
		std::cout << students[i].name
			<< std::string(maxlen + 1 - students[i].name.size(), ' ');

		// Compute and write the grade
		try {
			// Call grade() first as may throw exception
			double final_grade = grade(students[i]);

			std::streamsize prec = std::cout.precision();
			std::cout << std::setprecision(3) << final_grade
				<< std::setprecision((int)prec);
		}
		catch (std::domain_error &e) {
			std::cout << e.what();
		}
		std::cout << std::endl;
	}
	
	std::cout << "Finished - please type something to quit";
	int dummy;
	std::cin >> dummy;

	return 0;
}