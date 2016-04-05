#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <stdint.h>
#include <stdlib.h>

template <class T>
class buffer {
	public:
		buffer(uint32_t buf_size) {
			this->buf_size = buf_size;
			number_of_elements = 0;
			elements = (T*)calloc(buf_size, sizeof(T));
		}

		~buffer() {
			free(elements);
		}

		uint32_t count() {
			return number_of_elements;
		}

		uint32_t capacity() {
			return buf_size;
		}

		void remove_from(unsigned idx, T blank_element) {
			elements[idx] = blank_element;
			--number_of_elements;
		}

		void insert(unsigned idx, T element) {
			elements[idx] = element;
			++number_of_elements;
		}
	private:
		uint32_t buf_size;
		uint32_t number_of_elements;
		T* elements;
};

#endif