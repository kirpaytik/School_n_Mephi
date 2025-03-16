#include "Matrix.hpp"

#include <memory>


template <CellLike T> Matrix<T>::Matrix(int rows, int cols) :
	rows(rows), cols(cols)
{
	data = std::make_unique<std::unique_ptr<T[]>[]>(rows);
	for (int i = 0; i < rows; ++i) {
		data[i] = std::make_unique<T[]>(cols);
		for (int j = 0; j < cols; ++j) {
			data[i][j] = T(i, j);
		}
	}
}


template <CellLike T> void Matrix<T>::insert(T* value)
{
	int x = value->getX();
	int y = value->getY();
	if (x < 0 || x >= rows || y < 0 || y >= cols)
		throw std::out_of_range("Index out of bounds");

	data[x][y] = *value;
}


template <CellLike T> T* operator[](int i)
{
	if (i < 0 || i >= rows)
		throw std::out_of_range("Index out of bounds");

	return data[i].get();
}


template <CellLike T> const T* operator[](int i) const
{
	if (i < 0 || i >= rows)
		throw std::out_of_range("Index out of bounds");

	return data[i].get();
}


template <CellLike T> void remove(int x, int y)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols)
		throw std::out_of_range("Index out of bounds");

	data[i][j].~T();
	data[x][y] = T(x, y);
}


Iterator Matrix<T>::begin()
	{ return Iterator(data[0].get(), 0, 0, rows, cols); }

template <CellLike T> typename Matrix<T>::Iterator Matrix<T>::end()
	{ return Iterator(data[rows - 1].get() + cols, rows, cols, rows, cols); }


template <CellLike T> typename Matrix<T>::Iterator::reference Matrix<T>::Iterator::operator*() const
	{ return *ptr; }

template <CellLike T> typename Matrix<T>::Iterator::pointer Matrix<T>::Iterator::operator->() const
	{ return ptr; }

template <CellLike T> typename Matrix<T>::Iterator& Matrix<T>::Iterator::operator++()
{
	if (++col == cols) {
		col = 0;
		if (++row == rows) {
			ptr = nullptr;
		} else {
			ptr = data[row].get() + col;
		}
	} else {
		ptr++;
	}

	return *this;
}

template <CellLike T> typename Matrix<T>::Iterator Matrix<T>::Iterator::operator++(int)
{
	Iterator temp = *this;
	++(*this);
	return temp;
}


template <CellLike T> typename Matrix<T>::Iterator& Matrix<T>::Iterator::operator--()
{
	if (--col < 0) {
		if (--row < 0) {
			ptr = nullptr;
		} else {
			col = cols - 1;
			ptr = data[row].get() + col;
		}
	} else {
		ptr--;
	}

	return *this;
}

template <CellLike T> typename Matrix<T>::Iterator Matrix<T>::Iterator::operator--(int)
{
	Iterator temp = *this;
	--(*this);
	return temp;
}

template <CellLike T> typename Matrix<T>::Iterator Matrix<T>::Iterator::operator+(difference_type n)
{
	Iterator temp = *this;
	while (n > 0) {
		if (temp.col + n < temp.cols) {
			temp.col += n;
			temp.ptr += n;
			break;
		} else {
			n -= (temp.cols - temp.col);
			temp.col = 0;
			if (++temp.row == temp.rows) {
				temp.ptr = nullptr;
				break;
			}
			temp.ptr = data[temp.row].get();
		}
	}

	return temp;
}

template <CellLike T> typename Matrix<T>::Iterator Matrix<T>::Iterator::operator-(difference_type n)
{
	Iterator temp = *this;
	while (n > 0) {
		if (temp.col >= n) {
			temp.col -= n;
			temp.ptr -= n;
			break;
		} else {
			n -= (temp.col + 1);
			temp.col = temp.cols - 1;
			if (--temp.row < 0) {
				temp.ptr = nullptr;
				break;
			}
			temp.ptr = data[temp.row].get() + temp.col;
		}
	}

	return temp;
}


template <CellLike T> typename Matrix<T>::Iterator::difference_type Matrix<T>::Iterator::operator-(const Iterator& other) const
{
	if (row == other.row)
		return ptr - other.ptr;

	difference_type
	diff = (cols - col) + other.col;
	diff += (row - other.row - 1) * cols;

	return diff;
}


template <CellLike T> bool Matrix<T>::Iterator::operator==(const Iterator& other) const
	{ return ptr == other.ptr; }

template <CellLike T> bool Matrix<T>::Iterator::operator!=(const Iterator& other) const
	{ return ptr != other.ptr; }

template <CellLike T> bool Matrix<T>::Iterator::operator<(const Iterator& other) const
	{ return ptr < other.ptr; }

template <CellLike T> bool Matrix<T>::Iterator::operator>(const Iterator& other) const
	{ return ptr > other.ptr; }

template <CellLike T> bool Matrix<T>::Iterator::operator<=(const Iterator& other) const
	{ return ptr <= other.ptr; }

template <CellLike T> bool Matrix<T>::Iterator::operator>=(const Iterator& other) const
	{ return ptr >= other.ptr; }


template <CellLike T> typename Matrix<T>::Iterator::reference Matrix<T>::Iterator::operator[](difference_type n)
	{ return *(*this + n); }
