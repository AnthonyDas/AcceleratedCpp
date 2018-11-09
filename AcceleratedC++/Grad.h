#ifndef GUARD_grad_h
#define GUARD_grad_h

#include <iostream>
#include <algorithm> // min
#include "Core.h"

// Implementation of a grad (postgraduate) student, (p.228)
class Grad : public Core {

	double thesis;

public:

	// Default constructor - implicitly uses Core::Core() to initialise the base part (p.231)
	Grad() : thesis(0) {}

	Grad(std::istream &is) { read(is); } // (p.231)

	// Virtual by inheritance (p.230)
	std::istream& read(std::istream &);

	// Virtual by inheritance
	double grade() const {
		// Using scope operator to call Core::grade() is essential.
		// Otherwise, would recursively call Grad::grade() repeatedly.
		return std::min(Core::grade(), thesis);
	}

protected:

	// Virtual by inheritance
	// Employs synthesized copy constructor. (p.246)
	Grad* clone() const { return new Grad(*this); }
};

#endif