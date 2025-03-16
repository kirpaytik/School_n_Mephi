#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Cell.hpp"

#include <type_traits>
#include <memory>

template <typename T>
concept CellLike = std::is_base_of_v<Cell, T> && requires(T t, int x, int y) {
	{ t.getX() } -> std::same_as<int>;
	{ t.getY() } -> std::same_as<int>;
	{ T(x, y) }; // для создания пустого значения
};


template<CellLike T> class Matrix
{
private:
	std::unique_ptr<T[]> data;
	int rows;
	int cols;

public:
	Matrix(int rows, int cols) : rows(rows), cols(cols) {
		data = std::make_unique<T[]>(rows * cols);
		for (int i = 0; i < rows * cols; ++i) {
			data[i] = Cell(i / cols, i % cols);
		}
	}

	void insert(T* value) {
		int x = value->getX();
		int y = value->getY();
		if (x < 0 || x >= cols || y < 0 || y >= rows)
			throw std::out_of_range("Index out of bounds");

		data[y * cols + x] = *value;
	}

	void remove(int x, int y) {
		if (x < 0 || x >= cols || y < 0 || y >= rows)
			throw std::out_of_range("Index out of bounds");

		data[y * cols + x].~T();
		data[y * cols + x] = T(y, x);
	}


	class Row
	{
		friend class Matrix<T>;
	private:
		T* rowData;
		int cols;

		Row(T* rowData, int cols) : rowData(rowData), cols(cols) {}

	public:
		T& operator[](int j) {
			if (j < 0 || j >= cols)
				throw std::out_of_range("Column index out of bounds");

			return rowData[j];
		}

		const T& operator[](int j) const {
			if (j < 0 || j >= cols)
				throw std::out_of_range("Column index out of bounds");

			return rowData[j];
		}
	};


	Row operator[](int i) {
		if (i < 0 || i >= rows)
			throw std::out_of_range("Index out of bounds");

		return Row(data.get() + i * cols, cols);
	}

	const Row operator[](int i) const {
		if (i < 0 || i >= rows)
			throw std::out_of_range("Index out of bounds");

		return Row(data.get() + i * cols, cols);
	}


	class Iterator
	{
	private:
		T* ptr;

	public:
		// static assert
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		explicit Iterator(T* ptr) : ptr(ptr) {}

		reference operator*() const { return *ptr; }
		pointer operator->() const { return ptr; }
		Iterator& operator++() { ++ptr; return *this; }
		Iterator operator++(int) { Iterator temp = *this; ++(*this); return temp; }
		Iterator& operator--() { --ptr; return *this; }
		Iterator operator--(int) { Iterator temp = *this; --(*this); return temp;}
		Iterator operator+(difference_type n) const { return Iterator(ptr + n); }
		Iterator operator-(difference_type n) const { return Iterator(ptr - n); }
		difference_type operator-(const Iterator& other) const { return ptr - other.ptr; }
		bool operator==(const Iterator& other) const { return ptr == other.ptr; }
		bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
		bool operator<(const Iterator& other) const { return ptr < other.ptr; }
		bool operator>(const Iterator& other) const { return ptr > other.ptr; }
		bool operator<=(const Iterator& other) const { return ptr <= other.ptr; }
		bool operator>=(const Iterator& other) const { return ptr >= other.ptr; }

		reference operator[](difference_type n) { return *(*this + n); }
	};

	Iterator begin() const { return Iterator(data.get()); }
	Iterator end() const { return Iterator(data.get() + (rows * cols)); }
};

#endif
