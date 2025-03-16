#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Cell.hpp"

#include <type_traits>

template <typename T>
concept CellLike = std::is_base_of_v<Cell, T> && requires(T t, int x, int y) {
	{ t.getX() } -> std::same_as<int>;
	{ t.getY() } -> std::same_as<int>;
	{ T(x, y); } // для создания пустого значения
};


template <CellLike T> class Matrix
{
private:
	int rows, cols;
	std::unique_ptr<std::unique_ptr<T[]>[]> data;

public:
	Matrix(int rows, int cols);
	void insert(T* value);
	void remove(int row, int col);
	T* operator[](int i);
	const T* operator[](int i) const;


	class Iterator
	{
	private:
		T* ptr;
		int rows, cols;
		int row, col;

	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;

		explicit Iterator(T* ptr = Matrix::data.get()[0], int rows = Matrix::rows, int cols = Matrix::cols)
			: ptr(ptr), rows(rows), cols(cols), row(0), col(0) {}

		reference operator*() const;
		pointer operator->() const;
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		Iterator operator+(difference_type n);
		Iterator operator-(difference_type n);
		difference_type operator-(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
		bool operator<(const Iterator& other) const;
		bool operator>(const Iterator& other) const;
		bool operator<=(const Iterator& other) const;
		bool operator>=(const Iterator& other) const;

		reference operator[](difference_type n);
	};

	Iterator begin() const;
	Iterator end() const;
};

#endif
