#pragma once
#include <deque>
using std::deque;
struct Cell
{
	int x;
	int y;
	Cell operator=(const Cell& c1);
};

struct Field
{
	int** p;
	int xDim;
	int yDim;
};



enum Direction {UP, DOWN, LEFT, RIGHT};
enum CellContents{EMPTY_FIELD, SNAKE_BODY, TARGET};

class Snake
{
private:
	deque<Cell> _body;	
	Field _field;

public:
	
	Snake();
	Snake(int n, int m);
	~Snake();
	int move(Direction);
	bool inField(Cell& target);
    int** getField();
	int delay;

private:
	int** createField(const int n, const int m);
	void destroyField();
	void newTarget();
	void flashing();
	


};

