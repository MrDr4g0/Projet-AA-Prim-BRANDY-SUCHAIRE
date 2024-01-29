#pragma once
#include <iostream>

template <typename T>
class OurList {

	T* data;
	size_t size;
	size_t capacity;

public:
	OurList() : data(nullptr), size(0), capacity(0) {};

	OurList(size_t initialCapacity) : size(0), capacity(initialCapacity) {
		data = new T[capacity];
	}

	OurList(size_t initialCapacity, const T& element) : size(initialCapacity), capacity(initialCapacity) {
		data = new T[capacity];
		for (size_t i = 0; i < initialCapacity; ++i) {
			data[i] = element;
		}
	}

	OurList(const OurList& other) : size(other.size), capacity(other.capacity) {
		data = new T[capacity];
		for (size_t i = 0; i < size; ++i) {
			data[i] = other.data[i];
		}
	}

	~OurList() {
		delete[] data;
	}

	OurList& operator=(const OurList& other) {
		if (this != &other) {
			delete[] data;
			size = other.size;
			capacity = other.capacity;
			data = new T[capacity];

			for (size_t i = 0; i < size; ++i) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	T& operator[](size_t idx) {
		if (idx >= size) {
			throw std::out_of_range("OurList ERROR : Index given out of bounds ");
		}
		return data[idx];
	}

	const T& operator[](size_t idx) const {
		if (idx >= size) {
			throw std::out_of_range("OurList ERROR: Index given out of bounds");
		}
		return data[idx];
	}



	size_t getSize() const {
		return size;
	}

	void insert_back(const T& element) {
		if (size == capacity) {
			if (capacity == 0)
				capacity++;

			size_t newCapacity = 2 * capacity;
			T* newData = new T[newCapacity];

			for (size_t i = 0; i < size; ++i) {
				newData[i] = data[i];
			}

			delete[] data;
			data = newData;
			capacity = newCapacity;
		}

		data[size] = element;
		size++;
	}


	void remove(size_t position) {

		if (position >= size) {
			throw std::out_of_range("OurList ERROR: Index given out of bounds");
		}

		// Swap with the last element
		data[position] = data[size - 1];

		size--;

	}

	bool empty() const {
		return (size == 0);
	}

};
