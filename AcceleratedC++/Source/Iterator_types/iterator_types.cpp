

// 1. Sequential read-only access. (p.145)
template<typename In, typename X>
In find(In begin, In end, const X &x) {
	while (begin != end && *begin != x) {
		++begin;
	}

	return begin;
}


// 2. Sequential write-only access. (p.146)
template<typename In, typename Out>
Out copy(In begin, In end, Out dest) {
	while (begin != end) {
		*dest++ = *begin++;
	}

	return dest;
}

// 3. Sequential read-write access. (p.147)
template<typename For, typename X>
void replace(For begin, For end, const X &x, const X &y) {
	while (begin != end) {
		if (*begin == x) {
			*begin = y;
		}
		++begin;
	}
}

template<typename T>
void swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

// 4. Reversible read-write access. (p.148)
template<typename Bi>
void reverse(Bi begin, Bi end) {
	while (begin != end) {
		--end;
		if (begin != end) {
			// NB. we don't enter here to increment begin if begin == end
			swap(*begin++, *end);
		}
	}

	return begin;
}

// 5. Random read-write access. (p.148)
template<typename Ran, typename X>
bool binary_search(Ran begin, Ran end, const X &x) {
	while (begin < end ) {
		// Find the mid-point of the range
		Ran mid = begin + (end - begin) / 2;

		// See which part of the range contains x;
		// keep looking only in that part.
		if (x < *mid) {
			end = mid;
		}
		else if (*mid < x) {
			begin = mid + 1;
		}
		else { // *mid == x, so we're done
			return true;
		}
	}

	return false;
}