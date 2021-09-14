#include <stdio.h>

#include <list.hpp>

/* This project is for testing the list. */

/* Run a test. The function for the test must return true if the test passed
 * and return false if it failed. */
static void run_test(const char* name, std::function<bool()> func) {
	printf("Running test: '%s'... ", name);

	printf(func() ? "OK" : "FAILED");
	printf("\n");
}

/* Run all the tests */
void run_tests() {
	run_test("push_front", []() -> bool {
		list<int> l;
		l.push_front(2);
		l.push_front(5);
		return l.head->value == 5;
		});

	run_test("push_back", []() -> bool {
		list<int> l;
		l.push_back(2);
		l.push_back(5);
		return l.tail->value == 5;
		});

	run_test("count", []() -> bool {
		list<int> l;
		l.push_back(2);
		l.push_back(5);
		return l.count() == 2;
		});

	run_test("first", []() -> bool {
		list<int> l;
		l.push_front(2);
		l.push_front(5);
		return l.first()->value == 5;
		});

	run_test("last", []() -> bool {
		list<int> l;
		l.push_front(2);
		l.push_front(5);
		return l.last()->value == 2;
		});
}

int main() {
	run_tests();
}
