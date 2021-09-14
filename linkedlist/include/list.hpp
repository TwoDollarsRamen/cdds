#pragma once

#include <algorithm>
#include <functional>

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
	struct iterator {
		list_node<T>* node;

		explicit iterator(list_node<T>* n) {
			node = n;
		}

		bool valid() const {
			return node != nullptr;
		}

		T& value() const {
			return node->value;
		}

		iterator& operator++() {
			node = node->next;

			return *this;
		}

		iterator& operator--() {
			if (node->prev) {
				node = node->prev;
			}

			return *this;
		}

		bool operator==(const iterator& iter) {
			return iter.node == node;
		}

		bool operator!=(const iterator& iter) {
			return iter.node != node;
		}

		T* operator->() {
			return &node->value;
		}

		T& operator*() {
			return node->value;
		}
	};

	iterator begin() const {
		return iterator(head);
	}

	/* Null is the end of the list for the iterator */
	iterator end() const {
		return iterator(nullptr);
	}

	list_node<T>* head = nullptr;
	list_node<T>* tail = nullptr;

	/* Insert an element with value `v' after node `node'. */
	list_node<T>* insert(list_node<T>* node, const T& v) {
		auto new_node = new list_node<T>(v);

		if (node) {
			new_node->next = node->next;
			new_node->prev = node;

			if (node->next) {
				node->next->prev= new_node;
			}
			node->next = new_node;
		} else {
			if (!head) {
				head = new_node;
			} else {
				head->prev = new_node;
				new_node->next = head;
				head = new_node;
			}
		}

		if (!tail || node == tail) {
			tail = new_node;
		}

		return new_node;
	}

	/* Add an element with value `v' at the head
	 * of the list*/
	list_node<T>* push_front(const T& v) {
		return insert(nullptr, v);
	}

	/* Add an element with value `v' at the tail
	 * of the list */
	list_node<T>* push_back(const T& v) {
		return insert(tail, v);
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

	/* Remove the head */
	void remove_head() {
		remove(head);
	}

	/* Remove the tail */
	void remove_tail() {
		remove(tail);
	}

	/* Get the amount of elements in the list */
	int count() {
		int r = 0;

		for (const auto& i : *this) {
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

	/* Sort the list, using the function to
	 * compare the two values. */
	void sort(std::function<bool(const T&, const T&)> cmp) {
		if (!head) {
			return;
		} else {
			for (auto i = head; i->next; i = i->next) {
				for (auto j = i->next; j; j = j->next) {
					if (cmp(i->value, j->value)) {
						auto tmp = i->value;
						i->value = j->value;
						j->value = tmp;
					}
				}
			}
		}
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