#include <cctype> // strlen
#include <algorithm> // copy

// Caller must free memory that is allocated. (p.185)
char * duplicate_chars(const char* p) {
	// Allocated enough memory, remember to add one for the null terminator
	size_t length = strlen(p) + 1;
	char * result = new char[length];

	// Copy into our newly allocated space and return pointer to first element
	std::copy(p, p + length, result);
	return result;
}