#include <iostream>
#include <vector>
#include <algorithm> // max
#include <ios> // streamsize
#include <iomanip> // setprecision
#include <stdexcept> // domain_error
#include "Core.h"
#include "Grad.h"
#include "Handle.cpp"

// TODO
bool compare_Core_handles(const Handle<Core> &hc1, const Handle<Core> &hc2) {
	 return hc1->name() < hc2->name();
}

int main5() {

	std::vector<Handle<Core> > students;
	Handle<Core> record;
	std::string::size_type maxlen = 0; // Length of longest name

	// Read and store the data
	char ch;
	while (std::cin >> ch) {
		if (ch == 'U') {
			record = new Core; // Undergraduate student
		}
		else {
			record = new Grad; // Graduate student
		}

		record->read(std::cin);

		// Find length of longest name
		maxlen = std::max(maxlen, record->name().size());
		students.push_back(record);
	}

	// Sort the student records by name
	sort(students.begin(), students.end(), compare_Core_handles);

	// Write the names and grades
	for (std::vector<Handle<Core> >::size_type i = 0; i != students.size(); ++i) {

		// Write the name, padded on the right to maxlen + 1 characters
		std::cout << students[i]->name()
			<< std::string(maxlen + 1 - students[i]->name().size(), ' ');

		// Compute and write the grade
		try {
			// Call grade() first as may throw exception
			double final_grade = students[i]->grade();

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