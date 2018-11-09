#ifndef GUARD_core_h
#define GUARD_core_h

#include <iostream>
#include <string>
#include <vector>


// Implementation of a core (undergraduate) student, (p.228)
class Core {

	std::string n; // name - can already access via name()

protected:

	double midterm, final;

	std::vector<double> homework;

public:

	friend class Student_info2; // (p.246)

	// Default constructor (p.231)
	Core() : midterm(0), final(0) {}

	// Construct a Core from an istream (p.231)
	Core(std::istream &is) { read(is); }

	// Must include virtual destructor within a base class (p.242)
	virtual ~Core() {}

	std::string name() const { return n; } // (p.230)

	// (p.230, virtual p.234)
	virtual double grade() const;

	// (p.230, virtual p.236)
	virtual std::istream& read(std::istream &);

	// Employs synthesized copy constructor. (p.246)
	// Making public rather than protected. p.258
	virtual Core* clone() const { return new Core(*this); }

protected: // Accessible to derived classes (p.229)

	// (p.230)
	std::istream& read_common(std::istream &in) {
		// Read and store the student's name and exam scores
		in >> n >> midterm >> final;
		return in;
	}

};

// (p.232)
bool compare(const Core &c1, const Core &c2) {
	return c1.name() < c2.name();
}

// NB. Imperative that the parameters are passed by reference to
// invoke polymorphic call to grade(). (p.233)
bool compare_grades(const Core &c1, const Core &c2) {
	return c1.grade() < c2.grade();
}

#endif
