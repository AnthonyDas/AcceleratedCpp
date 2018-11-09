#include <list>
#include <vector>
#include <iterator> // back_inserter
#include <algorithm> // remove_copy_if, remove_if, stable_partition
#include "grade.h"
#include "Student_info.h"

// Predicate to determine whether a student failed. (p.75)
bool fgrade(const Student_info& s) {
	return grade(s) < 60;
}

// Predicate to determine whether a student passed. (p.117)
bool pgrade(const Student_info& s) {
	return !fgrade(s);
}

// Extracting fails using an appropriate container class that supports 
// efficient erasing from the middle of the container. (p.85)
std::list<Student_info> extract_fails(std::list<Student_info>& students) {

	std::list<Student_info> fail;
	std::list<Student_info>::iterator iter = students.begin();

	while (iter != students.end()) {
		if (fgrade(*iter)) {
			fail.push_back(*iter);
			iter = students.erase(iter);
		}
		else {
			++iter;
		}
	}

	return fail;
}


// Reimplementation of extract_fails() when container (vector) doesn't support 
// efficient erasing from the middle of the container. This attempt makes two
// passes over the container. (p.117)
std::vector<Student_info> extract_fails_one_pass(std::vector<Student_info>& students) {

	std::vector<Student_info> fail;
	
	std::remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade); // Pass 1

	students.erase(std::remove_if(students.begin(), students.end(), fgrade), students.end()); // Pass 2

	return fail;
}

// Reimplementation of extract_fails() when container (vector) doesn't support 
// efficient erasing from the middle of the container. This attempt makes a
// single pass over the container. The best approach! (p.119)
std::vector<Student_info> extract_fails_two_pass(std::vector<Student_info>& students) {

	std::vector<Student_info>::iterator iter = std::stable_partition(students.begin(), students.end(), pgrade);

	std::vector<Student_info> fail(iter, students.end());

	// Don't forget to remove fails from original vector
	students.erase(iter, students.end());

	return fail;
}