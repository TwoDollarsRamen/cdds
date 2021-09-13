#include "table.hpp"

namespace HashFunction {
	unsigned int hash(const void* in, int size) {
		unsigned int hash = 2166136261u;

		for (int i = 0; i < size; i++) {
			hash ^= (*(unsigned char*)in + size);
			hash *= 16777619;
		}

		return hash;
	}
}
