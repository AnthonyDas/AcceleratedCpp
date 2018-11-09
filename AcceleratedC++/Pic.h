#ifndef GUARD_Pic_h
#define GUARD_Pic_h

#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // max
#include "Ptr.cpp"

// Private classes used in the implementation only. (p.271)


class Picture; // Forward declaration (p.286, explanation p.288)

// Abstract base class. (p.276)
class Pic_base {
	// No public interface except of the destructor

	typedef std::vector<std::string>::size_type ht_sz;

	typedef std::string::size_type wd_sz;

	friend std::ostream& operator<<(std::ostream &, const Picture &); // (p.286)

	friend class String_Pic; // (p.286, explanation p.287)
	friend class Frame_Pic; // (p.286, explanation p.287)
	friend class VCat_Pic; // (p.286, explanation p.287)
	friend class HCat_Pic; // (p.286, explanation p.287)

public:

	virtual ~Pic_base() {} // (p.273)

protected:

	// (p.282)
	static void pad(std::ostream &os, wd_sz beg, wd_sz end) {
		while (beg != end) {
			os << " ";
			++beg;
		}
	}

private:

	virtual wd_sz width() const = 0; // Pure virtual

	virtual ht_sz height() const = 0; // Pure virtual

	virtual void display(std::ostream &, ht_sz, bool) const = 0; // Pure virtual
};


// Class which actually contains data provided by the user. (p.277)
class String_Pic : public Pic_base {
	// No public interface 
	
	// Picture requires access to String_Pic constructor (p.281)
	friend class Picture;

	std::vector<std::string> data; // Data provided by the user
	
	String_Pic(const std::vector<std::string> &v) : data(v) {}

	// (p.281)
	wd_sz width() const {
		wd_sz n = 0;
		for (ht_sz i = 0; i != data.size(); ++i) {
			n = std::max(n, data[i].size());
		}
		return n;
	}

	ht_sz height() const { return data.size(); } // (p.281)

	// (p.282)
	void display(std::ostream &os, ht_sz row, bool do_pad) const {
		wd_sz start = 0;

		// Write the row if we're still in range
		if (row < height()) {
			os << data[row];
			start = data[row].size();
		}

		// Pad the output if necessary
		if (do_pad) {
			pad(os, start, width());
		}
	}
};


// Framed picture. (p.276)
class Frame_Pic : public Pic_base {
	// No public interface 

	// Picture requires access to Frame_Pic constructor (p.285)
	friend Picture frame(const Picture &);

	Ptr<Pic_base> p; // Only stores a ptr to underlying Pic_base

	Frame_Pic(const Ptr<Pic_base> &pic) : p(pic) {}

	wd_sz width() const { return p->width() + 4; } // (p.285)

	ht_sz height() const { return p->height() + 4; } // (p.285)

	// (p.285)
	void display(std::ostream &os, ht_sz row, bool do_pad) const {
		if (row >= height()) {
			// Out of range
			if (do_pad)
				pad(os, 0, width());
		}
		else {
			if (row == 0 || row == height() - 1) {
				// Top or bottom row
				os << std::string(width(), '*');
			}
			else if (row == 1 || row == height() - 2) {
				// Second from top or bottom row
				os << "*";
				pad(os, 1, width() - 1);
				os << "*";
			}
			else {
				// Interior row
				os << "* ";
				p->display(os, row - 2, true); // Always pad interior rows to align right border
				os << " *";
			}
		}
	}
};


// Vertical concatenation. (p.277)
class VCat_Pic : public Pic_base {
	// No public interface 

	// Picture requires access to VCat_Pic constructor (p.283)
	friend Picture vcat(const Picture &, const Picture &);

	Ptr<Pic_base> top, bottom; // Only stores ptrs to underlying Pic_bases

	VCat_Pic(const Ptr<Pic_base> &t, const Ptr<Pic_base> &b) : top(t), bottom(b) {}

	wd_sz width() const { return std::max(top->width(), bottom->width()); } // (p.283)

	ht_sz height() const { return top->height() + bottom->height(); } // (p.283)

	// (p.284)
	void display(std::ostream &os, ht_sz row, bool do_pad) const {
		wd_sz w = 0;
		if (row < top->height()) {
			// We are in the top subpicture
			top->display(os, row, do_pad);
			w = top->width();
		}
		else if (row < height()) {
			// We are in the bottom subpicture
			bottom->display(os, row - top->height(), do_pad);
			w = bottom->width();
		}

		if (do_pad) {
			pad(os, w, width());
		}
	}
};


// Horizontal concatenation. (p.277)
class HCat_Pic : public Pic_base {
	// No public interface 

	// Picture requires access to HCat_Pic constructor (p.284)
	friend Picture hcat(const Picture &, const Picture &);

	Ptr<Pic_base> left, right; // Only stores ptrs to underlying Pic_bases

	HCat_Pic(const Ptr<Pic_base> &l, const Ptr<Pic_base> &r) : left(l), right(r) {}

	wd_sz width() const { return left->width() + right->width(); } // (p.284)

	ht_sz height() const { return std::max(left->height(), right->height()); } // (p.284)

	// (p.285)
	void display(std::ostream &os, ht_sz row, bool do_pad) const {
		left->display(os, row, do_pad || row < right->height());
		right->display(os, row, do_pad);
	}
};

#endif
