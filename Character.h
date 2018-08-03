#pragma once

#include "Window.h"
#include "Graph.h"

class Character
{
public:
	Character(Graph_lib::Window* win, int r, int c);
	void move();

	void setEnemy(Character* e) { my_enemy = e; }
	Character* enemy() { return my_enemy; }

	int row() { return pos_row; }
	int col() { return pos_col; }

protected:
	virtual pair<int, int> nextDirection();

	int pos_row;
	int pos_col;

	Graph_lib::Window* my_window;
	Character* my_enemy;

	//create Character's Shape
	vector<Graph_lib::Shape*> head_shapes;
	vector<Graph_lib::Shape*> body_shapes;
	vector<Graph_lib::Shape*> eye1_shapes;
	vector<Graph_lib::Shape*> eye2_shapes;


};

//create Pursuer class
class Pursuer : public Character
{
public:
	Pursuer(Graph_lib::Window* win, int r, int c);
protected:
	pair<int, int> nextDirection() override;
};

//create Evader class
class Evader : public Character
{
public:
	Evader(Graph_lib::Window* win, int r, int c);

protected:
	pair<int, int> nextDirection() override;
};

