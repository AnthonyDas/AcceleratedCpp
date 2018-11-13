#include <stdexcept> // runtime_error

/*
Member functions "T& opertor*() const" and "T* operator->() const"
preserve polymorphic behaviour as they yield either a reference or a
pointer.

This handle class always creates a copy of the underlying object.
Observe that both copy construct and assignment call clone() on the
target Handle's pointer. (p.255-256)
*/
template <typename T>
class Handle {

	T* p;

public:

	Handle() : p(0) {}

	Handle(T* t) : p(t) {}

	Handle(const Handle& h) : p(0) {
		if (h.p) { p = h.p->clone(); }
	}

	~Handle() { delete p; } // Delete is safe even on null ptr

	Handle& operator=(const Handle& rhs) {
		if (&rhs != this) { // Self-assignment guard
			delete p;
			p = rhs.p ? rhs.p->clone() : 0;
		}
		return *this;
	}

	operator bool() const { return p; }

	T& operator*() const {
		if (p) { return *p; }
		throw std::runtime_error("unbound Handle");
	}

	T* operator->() const {
		if (p) { return p; }
		throw std::runtime_error("unbound Handle");
	}

};
