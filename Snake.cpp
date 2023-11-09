#include "Snake.h"
#include <ctime>
#include <cstdlib>
bool Snake::inField(Cell& target)
{
	return (target.x >= 0) && (target.y >= 0) && 
			(target.x < _field.xDim) && (target.y < _field.yDim);
}

 int** Snake::getField()
{
	return _field.p;
}

Snake::Snake() : _field{}, _body{},delay{}
{
};

Snake::Snake( const int n, const int m)
{
	
	_body = { { n / 2, m / 2 - 1}, { n / 2, m / 2}, { n / 2, m / 2 + 1} };
	_field.p = createField(n, m);
	_field.xDim = n;
	_field.yDim = m;

	for (auto i : _body)
		_field.p[i.x][i.y] = 1;
	newTarget();
	delay={ 400 };
};	


Snake::~Snake()
{
	destroyField();
}

int** Snake::createField(const int n, const int m)
{
	
	int** field = new int* [n];
	for (int i{}; i < n; ++i)
	{
		field[i] = new int[m];
		for (int j{}; j < m; ++j)
			field[i][j] = 0;
	}
	
	return field;
}

void Snake::destroyField()
{	
		for (int i{}; i < _field.xDim; i++)
		{
			delete[] _field.p[i];
		}
		delete[] _field.p;
		_field.p = nullptr;	
}

void Snake::newTarget()
{
	
	bool rez; int x, y;
	do
	{
		 x = rand() % _field.xDim;
		 y = rand() % _field.yDim;
		rez = (_field.p[x][y] == EMPTY_FIELD);
	}
	
	while (!rez);
	_field.p[x][y] = TARGET;
}

void Snake::flashing()
{
}

Cell Cell::operator =(const Cell& c1)
{
	x = c1.x;
	y = c1.y;
	return *this;
}

int Snake::move(Direction dir)
{
	
	Cell target = _body.front();
	switch (dir)
	{
		case UP:
			--(target.y);
			break;
		case DOWN:
			++(target.y);
			break;
		case LEFT:
			--(target.x);
			break;
		case RIGHT:
			++(target.x);
			break;
	}

	if (inField(target))
		switch (_field.p[target.x][target.y])
		{
		case EMPTY_FIELD:
			_field.p[target.x][target.y] = 1;
			_field.p[_body.back().x][_body.back().y] = 0;
			_body.push_front(target);
			_body.pop_back();
			return 0;
			break;
		case SNAKE_BODY:
			flashing();
			return 1;
			break;
		case TARGET:
			_field.p[target.x][target.y] = 1;
			_body.push_front(target);
			newTarget();
			return 2;
			break;
		default:
			return -1;
			break;
		}
	else
		flashing();
		return -1;
	
}
