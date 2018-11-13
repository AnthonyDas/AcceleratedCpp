#include <stdexcept> // runtime_error

/*
Member functions "T& opertor*() const" and "T* operator->() const"
preserve polymorphic behaviour as they yield either a reference or a
pointer.

This handle class works well for underlying classes that can share state
between copies. E.g. classes that do not need valuelike behaviour. Or
classes that do not have any way of changing state once an object is
created. Observe that both copy construct and assignment merely copy the
target Ref_handle's pointers. (p.260-262)
*/
template <typename T>
class Ref_handle {

	T* p;

	size_t* refptr;

public:

	Ref_handle() : p(0), refptr(new size_t(1)) {}

	// Must never call this constructor multiple times with the same ptr.
	// To create multiple handles pointing to same ptr, use copy construct.
	Ref_handle(T* t) : p(t), refptr(new size_t(1)) {}

	Ref_handle(const Ref_handle& h) : p(h.p), refptr(h.refptr) {
		++(*refptr);
	}

	~Ref_handle() {
		// Decrement ref count, and if zero, delete underlying objects.
		if (--(*refptr) == 0) {
			delete refptr;
			delete p;
		}
	}

	Ref_handle& operator=(const Ref_handle& rhs) {
		// Self-assignment guard is subtle here. Increment ref count
		// on rhs before decrement on ref count on lhs. If both operands
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
		throw std::runtime_error("unbound Ref_handle");
	}

	T* operator->() const {
		if (p) { return p; }
		throw std::runtime_error("unbound Ref_handle");
	}

};
