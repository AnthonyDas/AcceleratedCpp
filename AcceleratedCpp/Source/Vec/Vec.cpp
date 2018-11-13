#include <memory> // allocator<T>
#include <algorithm> // max

// Implementation of our own vector class. (p.188)
template<typename T>
class Vec {
public:

	// (p.192)
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T& reference;
	typedef const T& const_reference;

private :

	iterator data; // First data element (p.189)

	iterator avail; // One past last constructed data element (p.203)

	iterator limit; // One past last allocated data element (p.189, p.203)

	std::allocator<T> alloc; // Object to handle memory allocation (p.206)

public:

	// Default constructor (p.190)
	Vec() { create(); }

	// Construct with n copies of val (p.190)
	explicit Vec(size_t n, const T& val = T()) { create(n, val); }
	
	// Copy constructor (p.195)
	Vec(const Vec &v) { create(v.begin(), v.end()); }

	// Destructor (p.200)
	~Vec() { uncreate(); }

	// Assignment (p.197)
	Vec& operator= (const Vec &rhs) {
		// Self-assignment guard
		if (&rhs != this) {

			// Free the array in the lhs
			uncreate();

			// copy the elements from the rhs to the lhs
			create(rhs.begin(), rhs.end());
		}
		return *this;
	}

	size_type size() const { return avail - data; } // (p.193)

	T& operator[](size_type i) { return data[i]; } // (p.193)

	const T& operator[](size_type i) const { return data[i]; } // (p.193)

	// (p.203)
	void push_back(const T& val) {
		// Get space if needed
		if (avail == limit) {
			grow();
		}
		// Append the new element
		unchecked_append(val);
	}

	void clear() {
		if (data) {
			// Destroy (in reverse order) the elements that were contructed
			iterator it = avail; // One past last constructed
			while (it != data) {
				alloc.destroy(--it);
			}
			avail = data;
		}
	}

	iterator begin() { return data; } // (p.194)
	const_iterator begin() const { return data; } // (p.194)

	iterator end() { return avail; } // (p.193)
	const_iterator end() const { return avail; } // (p.193)

private:

	// create() methods - allocate and initialise the underlying array (p.207)
	void create() { data = avail = limit = 0; }

	void create(const size_t &n, const T& val) {
		data = alloc.allocate(n);
		limit = avail = data + n;
		std::uninitialized_fill(data, limit, val);
	}

	void create(const_iterator i, const_iterator j) {
		data = alloc.allocate(j - i);
		limit = avail = std::uninitialized_copy(i, j, data); // begin, end, destination
	}


	// Destroy the elements in the array and free the memory (p.208)
	void uncreate() {
		if (data) {
			// Destroy (in reverse order) the elements that were contructed
			iterator it = avail; // One past last constructed
			while (it != data) {
				alloc.destroy(--it);
			}

			// Return all the space that was allocated
			alloc.deallocate(data, limit - data);

			// Reset pointers to indicate Vec is empty again
			data = avail = limit = 0;
		}
	}

	// Support function for push_back (p.208)
	void grow() {
		// When growing, allocate twice as much space as currently in use.
		// Types passed to max must be identical.
		size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

		// Allocate new space and copy existing elements to new space
		iterator new_data = alloc.allocate(new_size);
		iterator new_avail = std::uninitialized_copy(data, avail, new_data);

		// Return old space
		uncreate();

		// Reset pointers to point to the newly allocated space
		data = new_data;
		avail = new_avail;
		limit = data + new_size;
	}

	// Support function for push_back.
	// Assumes avail points at allocated but uninitialised space. (p.208)
	void unchecked_append(const T& val) {
		alloc.construct(avail++, val);
	}

};
