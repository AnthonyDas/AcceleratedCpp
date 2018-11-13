#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

// Student_info.h (p.68)
#include <iostream>
#include <string>
#include <vector>

// (p.62)
struct Student_info {

	std::string name;

	double midterm, final;

	std::vector<double> homework;

};

bool compare_Student_info(const Student_info&, const Student_info&);

bool did_all_hw(const Student_info&);

std::istream& read_hw(std::istream&, std::vector<double>&);

std::istream& read(std::istream&, Student_info&);

#endif
