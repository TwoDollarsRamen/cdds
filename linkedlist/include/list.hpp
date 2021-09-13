#pragma once

/* Represents a single list node */
template <typename T>
struct list_node {
	T value;
	list_node<T>* next = nullptr;
	list_node<T>* prev = nullptr;

	list_node(T v) {
		value = v;
	}
};

/* Implements a double linked list
 *
 * The entirety of this structure is
 * implemented in the header, since that is
 * required for templates. */
template <typename T>
struct list {
	list_node<T>* head = nullptr;
	list_node<T>* tail = nullptr;

	/* Insert an element with value `v' after node `node'. */
	list_node<T>* insert(list_node<T>* node, const T& v) {
		auto new_node = new list_node<T>(v);

		new_node->next = node;

		if (node) {
			new_node->prev = node->prev;

			if (node->prev) {
				node->prev->next = new_node;
			}
			node->prev = new_node;
		}

		if (head == node) {
			head = new_node;
		}

		if (!tail) {
			tail = new_node;
		}

		return new_node;
	}

	/* Remove node `node' */
	void remove(list_node<T>* node) {
		if (!head || !node) { return; }

		if (head == node) {
			head = node->next;
		}

		if (tail == node) {
			tail = node->prev;
		}

		if (node->next) {
			node->next->prev = node->prev;
		}

		if (node->prev) {
			node->prev->next = node->next;
		}

		delete node;
	}

	/* Add an element with value `v' at the head
	 * of the list*/
	list_node<T>* push_front(const T& v) {
		return insert(head, v);
	}

	/* Add an element with value `v' at the tail
	 * of the list */
	list_node<T>* push_back(const T& v) {
		return insert(tail, v);
	}

	/* Get the amount of elements in the list */
	int count() {
		auto cur = head;

		int r = 0;

		while (cur) {
			cur = cur->next;

			r++;
		}

		return r;
	}

	/* Get the head */
	list_node<T>* first() {
		return head;
	}

	/* Get the tail */
	list_node<T>* last() {
		return tail;
	}

	/* Is the list empty? */
	bool empty() { return !head; }

	/* Sort the list. */
	void sort() {

	}

	~list() {
		auto cur = head;

		while (cur) {
			auto temp = cur;
			cur = cur->next;
			delete temp;
		}
	}
};
