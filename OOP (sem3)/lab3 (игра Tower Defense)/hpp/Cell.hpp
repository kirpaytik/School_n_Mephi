#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
protected:
	int x, y;
public:
	Cell(); // для шаблонки нужен и пустой:(
	Cell(int x, int y);

	int getX() const;
	int getY() const;
	void setX(int newx);
	void setY(int newy);
};

#endif
