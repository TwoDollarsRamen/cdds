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
 * Almost the entirety of this structure is
 * implemented in the header, since that is
 * required for templates. */
template <typename T>
struct list {
	list_node<T>* head = nullptr;
	list_node<T>* tail = nullptr;

	list_node<T>* insert(list_node<T>* node, const T& v) {
		list_node<T>* nn = new list_node<T>(v);

		nn->next = node;

		if (node) {
			nn->prev = node->prev;

			if (node->prev) {
				node->prev->next = nn;
			}
			node->prev = nn;
		}

		if (head == node) {
			head = nn;
		}

		if (!tail) {
			tail = nn;
		}

		return nn;
	}

	void remove(list_node<T>* node) {
		if (!head || !node) { return; }

		if (head == node) {
			head = node->next;
		}

		if (node->next) {
			node->next->prev = node->prev;
		}

		if (node->prev) {
			node->prev->next = node->next;
		}

		delete node;
	}

	list_node<T>* push_front(const T& v) {
		return insert(head, v);
	}

	list_node<T>* push_back(const T& v) {
		return insert(tail, v);
	}

	int count() {
		list_node<T>* cur = head;

		int r = 0;

		while (cur) {
			cur = cur->next;

			r++;
		}

		return r;
	}

	list_node<T>* first() {
		return head;
	}

	list_node<T>* last() {
		return tail;
	}

	bool empty() { return !head; }

	~list() {
		list_node<T>* cur = head;

		while (cur) {
			list_node<T>* temp = cur;
			cur = cur->next;
			delete temp;
		}
	}
};
