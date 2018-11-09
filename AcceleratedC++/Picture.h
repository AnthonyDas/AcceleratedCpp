#ifndef GUARD_Picture_h
#define GUARD_Picture_h

#include <vector>
#include <string>
#include <iostream>
#include "Pic.h"
#include "Ptr.cpp"

// Public interface class giving access to operations. (p.271)

class Picture {

	Ptr<Pic_base> p;

public:

	friend Picture frame(const Picture &); // (p.287)

	friend Picture hcat(const Picture &, const Picture &); // (p.287)

	friend Picture vcat(const Picture &, const Picture &); // (p.287)

	friend std::ostream& operator<<(std::ostream &, const Picture &); // (p.287)

	Picture(const std::vector<std::string> &v = std::vector<std::string>()) : p(new String_Pic(v) {} // (p.280)

private:

	// Needed for auto conversions from Pic_base* to Picture. (p.279)
	Picture(Pic_base* ptr) : p(ptr) {} 

};

// (p.271, p.279)
Picture frame(const Picture &pic) {
	return new Frame_Pic(pic.p);
}

// (p.271, p.280)
Picture hcat(const Picture &l, const Picture &r) {
	return new HCat_Pic(l.p, r.p);
}

// (p.271, p.280)
Picture vcat(const Picture &t, const Picture &b) {
	return new VCat_Pic(t.p, b.p);
}


// (p.271, p.280)
std::ostream& operator<<(std::ostream &os, const Picture &pic) {
	const Pic_base::ht_sz ht = pic.p->height();
	for (Pic_base::ht_sz i = 0; i != ht; ++i) {
		pic.p->display(os, i, false);
		os << std::endl;
	}
	return os;
}


#endif