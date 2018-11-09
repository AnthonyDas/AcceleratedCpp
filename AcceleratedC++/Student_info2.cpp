#include <iostream>
#include "Core.h"
#include "Grad.h"

// (p.243)
class Student_info2 {

	Core* cp;

public:

	Student_info2() : cp(0) {}

	Student_info2(std::istream &is) : cp(0) { read(is); }

	// (p.247)
	Student_info2(const Student_info2 &s) : cp(0) {
		if (s.cp) { cp = s.cp->clone(); }
	}

	~Student_info2() { delete cp; }

	// (p.247)
	Student_info2& operator=(const Student_info2 &s) {
		if (&s != this) { // Self-assignment guard
			delete cp;
			if (s.cp) {
				cp = s.cp->clone();
			}
			else {
				cp = 0;
			}
		}
		return *this;
	}

	std::string name() const {
		if (cp) { return cp->name(); }
		throw std::runtime_error("uninitialised Student_info2");
	}

	double grade() const {
		if (cp) { return cp->grade(); }
		throw std::runtime_error("uninitialised Student_info2");
	}

	// (p.245)
	std::istream& read(std::istream &is) {
		delete cp; // Delete previous object if any

		// Get the record type
		char ch;
		is >> ch;

		if (ch == 'U') {
			cp = new Core(is); // Undergraduate student
		}
		else {
			cp = new Grad(is); // Graduate student
		}

		return is;
	}

	// NB. Static - gives it a qualified name Student_info2::compare() for sort. (p.244)
	static bool compare(const Student_info2 &s1, const Student_info2 &s2) {
		return s1.name() < s2.name();
	}

};
