#include <iostream>
#include "Grad.h"
#include "Student_info.h" // read_hw()


// Virtual by inheritance (p.230)
std::istream& Grad::read(std::istream &in) {
	read_common(in);
	in >> thesis;
	read_hw(in, homework);
	return in;
}

