#pragma once

#include <stdexcept>
#include <functional>

#include <stdlib.h>

/* Something about PascalCase really irritates me. */
namespace HashFunction {
	/* Grow when the table is 75% full. */
	static const double table_max_load = 0.75;

	/* Implements the FNV-1a hashing algorithm */
	unsigned int hash(const void* in, int size);

	template <typename...> struct table_el;
	template <typename...> struct table;

	/* == NOTES == 
	 *
	 * Collision resolution is handled using the open addressing
	 * method. If there is a collison, we search for the next empty
	 * bucket. I'm using linear probing to figure that out
	 * because I couldn't figure out how quadratic probing
	 * works in such a short time frame... Maybe when I
	 * find the time I will come back to this and try a different
	 * probing method again. */

	/* A table element, or `bucket' */
	template <typename key_t, typename value_t>
	struct table_el<key_t, value_t> {
		key_t key;
		value_t value;

		/* is_null marks the element as being empty,
		 * to the table, this means it doesn't exist
		 * at all.
		 *
		 * is_tombstone marks the element as being
		 * recently deleted. The reason why we can't just
		 * set is_null to true on deletion is because of the
		 * way that I chose to handle collision resolution.
		 * If the element is null, it is returned in the 
		 * find function. This means any entries after it
		 * are unreachable. is_tombstone is used as a flag
		 * to skip over the entry, instead of returning it.
		 * Then, when another null entry is found, we instead
		 * return the first tombstone, instead of the null
		 * entry. */
		bool is_null = true;
		bool is_tombstone = false;
	};

	/* This function is not part of the hashtable struct,
	 * since it is used to find elements in a new array
	 * when the table is resized. */
	template <typename key_t, typename value_t>
	table_el<key_t, value_t>* find_element(table_el<key_t, value_t>* els, int capacity, const key_t& key) {
		int idx = hash(&key, sizeof(key)) % capacity;

		table_el<key_t, value_t>* tombstone = nullptr;

		for (;;) {
			table_el<key_t, value_t>* e = &els[idx];
			if (e->is_null) {
				if (e->is_tombstone) {
					if (!tombstone) { tombstone = e; }
				} else {
					return tombstone ? tombstone : e;
				}
			} else if (e->key == key) {
				return e;
			}

			idx = (idx + 1) % capacity;
		}
	}

	/* Implements a generic hash table.
	 *
	 * Hashes based on the raw bytes of the key.
	 *
	 * The keys must have the `==' and the `=' operators
	 * overloaded. The value needs the `=' operator overloaded. */
	template <typename key_t, typename value_t>
	struct table<key_t, value_t> {
		table_el<key_t, value_t>* elements = nullptr;
		int count = 0;
		int capacity = 0;

		void resize(int new_capacity) {
			/* So, I was using malloc to allocate here, as I do normally for buffers.
			 * 
			 * It was crashing when working with std::strings, turns out move semantics
			 * completely fail when you use malloc. That was a waste of 20 minutes. */
			table_el<key_t, value_t>* els = new table_el<key_t, value_t>[new_capacity];
			for (int i = 0; i < new_capacity; i++) {
				els[i].is_null = true;
				els[i].is_tombstone = false;
			}

			for (int i = 0; i < capacity; i++) {
				table_el<key_t, value_t>* el = &elements[i];
				if (el->is_null) { continue; }

				table_el<key_t, value_t>* dst = find_element(els, new_capacity, el->key);
				dst->is_null = false;
				dst->value = el->value;
			}

			if (elements) {
				delete[] elements;
			}

			elements = els;
			capacity = new_capacity;
		}

		/* Set a key's value, create it if required. */
		void set(const key_t& key, const value_t& value) {
			/* Resize the array if the capacity overflows the load factor */
			if (count >= (double)capacity * table_max_load) {
				int new_capacity = capacity < 8 ? 8 : capacity * 2;
				resize(new_capacity);
			}

			/* Find the element. If it's null, it means the element is new
			 * to the table and it isn't simply an old key being reset. */
			table_el<key_t, value_t>* el = find_element(elements, capacity, key);
			if (el->is_null) {
				count++;
			}

			el->is_null = false;
			el->is_tombstone = false;
			el->key = key;
			el->value = value;
		}

		/* Get a value at a key. */
		value_t& get(const key_t& key) {
			if (count == 0) { throw std::out_of_range("Key not found in table."); }

			table_el<key_t, value_t>* el = find_element(elements, capacity, key);
			if (el->is_null) { throw std::out_of_range("Key not found in table."); }

			return el->value;
		}

		const value_t& get(const key_t& key) const {
			if (count == 0) { throw std::out_of_range("Key not found in table."); }

			table_el<key_t, value_t>* el = find_element(elements, capacity, key);
			if (el->is_null) { throw std::out_of_range("Key not found in table."); }

			return el->value;
		}

		void remove(const key_t& key) {
			if (count == 0) { return; }

			table_el<key_t, value_t>* el = find_element(elements, capacity, key);
			if (el->is_null) { return; }

			/* Mark this entry as a tombstone */
			el->is_null = true;
			el->is_tombstone = true;

			count--;
		}

		const value_t& operator[](const key_t& key) const {
			return get(key);
		}

		value_t& operator[](const key_t& key) {
			return get(key);
		}

		~table() {
			delete[] elements;
		}
	};
};
