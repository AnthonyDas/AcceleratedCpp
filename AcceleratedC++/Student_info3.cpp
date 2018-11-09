#include <iostream>
#include "Core.h"
#include "Grad.h"
#include "Handle.cpp"

// Instead of having a pointer to Core/Grad, now delegates management of
// pointer to Handle. So class can become a pure interface class. (p.258)
class Student_info3 {

	Handle<Core> cp;

public:

	Student_info3() {}

	Student_info3(std::istream &is) { read(is); }

	// No copy, assign or destructor - they're no longer needed. (p.258)
	
	std::string name() const {
		if (cp) { return cp->name(); }
		throw std::runtime_error("uninitialised Student_info3");
	}

	double grade() const {
		if (cp) { return cp->grade(); }
		throw std::runtime_error("uninitialised Student_info3");
	}

	// (p.259)
	std::istream& read(std::istream &is) {
		// Get the record type
		char ch;
		is >> ch;

		// Allocate new object of the appropriate type.
		// Use Handle<T>(T*) to build Handle<Core> from pointer to that object.
		// Call Handle<T>::operator= to assign to the Handle<Core> to the lhs
		if (ch == 'U') {
			cp = new Core(is); // Undergraduate student
		}
		else {
			cp = new Grad(is); // Graduate student
		}

		return is;
	}

	// NB. Static - gives it a qualified name Student_info2::compare() for sort. (p.244)
	static bool compare(const Student_info3 &s1, const Student_info3 &s2) {
		return s1.name() < s2.name();
	}

};
