#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <filesystem>

#include "table.hpp"

using namespace HashFunction;

table<std::string, int> entries;

static int command(int argc, const char** argv) {
	if (argc > 0) {
		if (strcmp(argv[0], "exit") == 0) {
			return 1;
		} else if (strcmp(argv[0], "help") == 0) {
			printf(
				"Possible commands:\n"
				"	set <key> <value>	set a string key to a integer value.\n"
				"	get <key>		get and print the value of a key.\n"
				"	del <key>		remove a key value pair\n"
				"	exit			quit the application.\n"
				"	help			display a list of possible commands.\n");
		}
	}
	if (argc > 1) {
		if (strcmp(argv[0], "get") == 0) {
			/* Yes, I know catching exceptions are slow.
			 *
			 * This application was never designed with
			 * performance in mind. */
			try {
				printf("%d\n", entries[argv[1]]);
			} catch (const std::exception& e) {
				printf("%s\n", e.what());
			}
		} else if (strcmp(argv[0], "del") == 0) {
			entries.remove(argv[1]);
		}
	}
	if (argc > 2) {
		if (strcmp(argv[0], "set") == 0) {
			entries.set(argv[1], atoi(argv[2]));
		}
	}

	return 0;
}

static void repl() {
	char line[1024];
	for (;;) {
		printf("[hashtable]$ ");

		if (!fgets(line, sizeof(line), stdin)) {
			printf("\n");
			break;
		}

		/* Remove the newline */
		line[strlen(line) - 1] = '\0';

		/* Parse the input into an array of strings
		 * split by spaces, so that commands can
		 * take arguments. */
		const char* argv[256];
		int argc = 0;

		const char* tok = strtok(line, " ");
		while (tok != nullptr) {
			argv[argc++] = tok;

			tok = strtok(nullptr, " ");
		}

		if (command(argc, argv) != 0) {
			return;
		}
	}
}

int main() {
	repl();
}
