#include <stdexcept> // runtime_error
#include <vector>

template <typename T>
T* clone(const T* p) {
	return p->clone();
}

// And if a class doesn't implement clone(), then we can
// define our own version as follows, for example:
template <>
std::vector<char>* clone(const std::vector<char>* vp) {
	return new std::vector<char>(*vp);
}

/*
Member functions "T& opertor*() const" and "T* operator->() const"
preserve polymorphic behaviour as they yield either a reference or a
pointer.

This handle class works well for underlying classes that can share state
between copies but also provides functionality for valuelike behaviour by 
calling make_unique() which ultimately calls clone(). (p.263-267)
*/
template <typename T>
class Ptr {

	T* p;

	size_t* refptr;

public:

	// Set refptr to 1. In destructor we decrement, and if zero, call delete.
	Ptr() : p(nullptr), refptr(new size_t(1)) {}

	// Must never call this constructor multiple times with the same ptr.
	// To create multiple handles pointing to same ptr, use copy construct.
	Ptr(T* t) : p(t), refptr(new size_t(1)) {}

	Ptr(const Ptr &h) : p(h.p), refptr(h.refptr) {
		++(*refptr);
	}

	~Ptr() {
		// Decrement ref count, and if zero, delete underlying objects.
		if (--(*refptr) == 0) {
			delete refptr;
			delete p;
		}
	}

	// Copy the object conditionally when needed.
	void make_unique() {
		if (*refptr != 1) {
			--(*refptr);
			refptr = new size_t(1);
			
			// This forces underlying object to always define clone.
			// Instead, introduce a layer of indirection which either
			// calls p->clone() if it exists, or our own implementation
			// if it doesn't through our template specialisation.
			// p = p ? p->clone() : nullptr;
			p = p ? clone(p) : nullptr; // Call global (non-member) clone()
		}
	}

	Ptr& operator=(const Ptr &rhs) {
		// Self-assignment guard is subtle here. Increment ref count
		// on rhs before decrement ref count on lhs. If both operands
		// refer to the same object, the net effect will be to leave ref
		// count unchanged.
		++(*(rhs.refptr));

		if (--(*refptr) == 0) {
			delete refptr;
			delete p;
		}

		// Copy in values from rhs
		refptr = rhs.refptr;
		p = rhs.p;

		return *this;
	}

	operator bool() const { return p; }

	T& operator*() const {
		if (p) { return *p; }
		throw std::runtime_error("unbound Ptr");
	}

	T* operator->() const {
		if (p) { return p; }
		throw std::runtime_error("unbound Ptr");
	}

};
