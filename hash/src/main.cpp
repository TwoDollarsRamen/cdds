#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <filesystem>

#include "table.hpp"

using namespace HashFunction;

/* I had this lying around from an old C project.
 * Fairly certain the C file API is faster than the C++ one.
 *
 * It's pretty generic, `term' specifies whether a null terminator
 * should be added to the end of the data, so it can load strings
 * as well as binary data. */
unsigned char* read_file(const char* path, int* size, bool term) {
	FILE* file = fopen(path, "rb");
	if (!file) {
		fprintf(stderr, "failed to open `%s'.\n", path);
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	rewind(file);

	unsigned char* buffer = (unsigned char*)malloc(file_size + (term ? 1 : 0));
	int bytes_read = (int)fread(buffer, sizeof(char), file_size, file);
	if (term) {
		buffer[bytes_read] = '\0';
	}

	if (size) {
		*size = file_size + (term ? 1 : 0);
	}

	fclose(file);
	return buffer;
}

struct binary_buffer {
	unsigned char* data;
	int size;
};

int main() {
	table<std::string, binary_buffer> files;

	binary_buffer b = { 0 };
	b.data = read_file("include/table.hpp", &b.size, true);

	files.set("include/table.hpp", b);

	printf("%s\n", files["include/table.hpp"].data);

	free(files["include/table.hpp"].data);
}
