#include "Character.h"

using namespace Graph_lib;

const int grid_width = 8;
const int grid_height = 8;

Character::Character(Graph_lib::Window* win, int r, int c)
	: my_window{ win }, pos_row { r }, pos_col{ c }, my_enemy{ nullptr }
{
}

void Character::move()
{
	pair<int, int> dir = nextDirection();

	int dr = dir.first;
	int dc = dir.second;
	pos_row += dr;
	pos_col += dc;

	int w = my_window->x_max() / grid_width;
	int h = my_window->y_max() / grid_height;
	for (Shape* s : head_shapes)
	{
		s->move(w*dc, h*dr);
	}
	for (Shape* s : body_shapes)//for moving body
	{
		s->move(w*dc, h*dr);
	}
	for (Shape* s : eye1_shapes)//for moving eye1
	{
		s->move(w*dc, h*dr);
	}
	for (Shape* s : eye2_shapes)//for moving eye2
	{
		s->move(w*dc, h*dr);
	}
}

pair<int, int> Character::nextDirection()
{
	return make_pair(0, 0);
}



Pursuer::Pursuer(Graph_lib::Window * win, int r, int c)
	: Character(win, r, c)
{
	int w = win->x_max() / grid_width;
	int h = win->y_max() / grid_height;

	//setting Pursuer Character
	Graph_lib::Ellipse* head = new Graph_lib::Ellipse(Point(c*w + w / 2, r*h + h / 4), w / 4, h / 4);
	head_shapes.push_back(head);
	Graph_lib::Rectangle* body = new Graph_lib::Rectangle(Point(c*w + w / 4, r*h + h / 2), w / 2, h / 2);
	body->set_fill_color(Color::red);
	body_shapes.push_back(body);
	Graph_lib::Star* eye1 = new Graph_lib::Star(Point(c*w + w / 2.5, r*h + h / 4), 4, 6, 12);
	eye1->set_color(Color::yellow);
	eye1_shapes.push_back(eye1);
	Graph_lib::Star* eye2 = new Graph_lib::Star(Point(c*w + w / 1.7, r*h + h / 4), 4, 6, 12);
	eye2->set_color(Color::yellow);
	eye2_shapes.push_back(eye2);

	win->attach(*head);
	win->attach(*body);
	win->attach(*eye1);
	win->attach(*eye2);
}


Evader::Evader(Graph_lib::Window * win, int r, int c)
	: Character(win, r, c)
{
	int w = win->x_max() / grid_width;
	int h = win->y_max() / grid_height;
	//setting Evader Character
	Graph_lib::Ellipse* head = new Graph_lib::Ellipse(Point(c*w + w / 2, r*h + h / 4), w / 4, h / 4);
	head_shapes.push_back(head);
	Graph_lib::Rectangle* body = new Graph_lib::Rectangle(Point(c*w + w / 4, r*h + h / 2), w / 2, h / 2);
	body->set_fill_color(Color::blue);
	body_shapes.push_back(body);
	Graph_lib::Regular_polygon* eye1 = new Graph_lib::Regular_polygon(Point(c*w + w / 2.5, r*h + h / 4), 4, 12);
	eye1->set_color(Color::blue);
	eye1_shapes.push_back(eye1);
	Graph_lib::Regular_polygon* eye2 = new Graph_lib::Regular_polygon(Point(c*w + w / 1.7, r*h + h / 4), 4, 12);
	eye2->set_color(Color::blue);
	eye2_shapes.push_back(eye2);

	win->attach(*head);
	win->attach(*body);
	win->attach(*eye1);
	win->attach(*eye2);
}


pair<int, int> Pursuer::nextDirection()
{
	vector<pair<int, int>> directions = { { -1,0 },{ +1,0 },{ 0,-1 },{ 0,+1 } };
	random_shuffle(directions.begin(), directions.end());

	int dr = 0;
	int dc = 0;
	int enemy_row = my_enemy->row();//enemy's row
	int enemy_col = my_enemy->col();//enemy's col
	int new_r = 0;
	int new_c = 0;
	int now_row = pos_row;
	int now_col = pos_col;

	for (int i = 0; i < 4; i++)
	{
		if (enemy_row > now_row) { //if enemy is lower than me
			if (enemy_col > now_col)//if enemy is on my right side
				directions = { {+1,0}, {0, +1} };//move up or right
			else if (enemy_col < now_col)//if enemy is on my left side
				directions = { { +1,0 },{ 0,-1 } };//move down or left
			else//if enemy is on my bottom side
				directions = { { +1,0 } };

		}
		else if (enemy_row < now_row) { //if enemy is higher than me
			if (enemy_col > now_col)//if enemy is on my right side
				directions = { { -1,0 },{ 0, +1 } };//move up or right
			else if (enemy_col < now_col)//if enemy is on my left side
				directions = { { -1,0 },{ 0, -1 } };//move up or left
			else//if enemy is on my top side
				directions = { { -1,0 } };//move up
		}
		else { //if enemy is on the same row
			if (enemy_col > now_col)//same right side row
				directions = { { 0, +1 } };
			else if (enemy_col < now_col)//same left side row
				directions = { { 0, -1 } };
		}

		random_shuffle(directions.begin(), directions.end());//random
		dr = directions[i].first;//save random direction
		dc = directions[i].second;
		new_r = now_row + dr;
		new_c = now_col + dc;
		if (new_r >= 0 && new_r < grid_height && new_c >= 0 && new_c < grid_width)//for not to go over the box
		{
			return directions[i];
		}
	}
}



pair<int, int> Evader::nextDirection()
{
	vector<pair<int, int>> directions = { { -1,0 },{ +1,0 },{ 0,-1 },{ 0,+1 } };
	random_shuffle(directions.begin(), directions.end());



	int dr = 0;
	int dc = 0;
	int enemy_row = my_enemy->row();//enemy's row
	int enemy_col = my_enemy->col();//enemy's col
	int new_r = 0;
	int new_c = 0;
	int now_row = pos_row;
	int now_col = pos_col;

	for (int i = 0; i < 3; i++)
	{
		if (now_col < enemy_col) {//if enemy is on my right side
			if (now_row < enemy_row) directions = { {-1,0}, {+1,0}, {0,-1} };//if enemy is lower than me
			else if (now_row > enemy_row) directions = { {+1,0}, {-1,0}, {0,-1} };//if enemy is higher than me
			else if (now_row = enemy_row) directions = { {+1,0},{-1,0},{0,-1} };//if enemy is on the same row with me
			else directions = { { +1,0 },{ -1,0 },{ 0,-1 } };//for exception
		}
		else if (now_col > enemy_col) {//if enemy is on my left side
			if (now_row < enemy_row) directions = { { -1,0 },{+1,0}, { 0,+1 } };//if enemy is lower than me
			else if (now_row > enemy_row) directions = { { +1,0 },{-1,0}, { 0,+1 } };//if enemy is higher than me
			else if (now_row = enemy_row) directions = { { +1,0 },{ -1,0 },{ 0,+1 } };//if enemy is on the same row with me
			else directions = { { +1,0 },{ -1,0 },{ 0,+1 }  };//for exception
		}
		else {//if enemy is on the same col with me
			if (now_row < enemy_row) directions = { {-1,0}, {0,+1}, {0,-1} };//if enemy is on the bottom side
			else if (now_row > enemy_row) directions = { {+1,0},{0,-1},{0,+1} };//if enemy is on the top side
			else directions = { { 0,0 },{ 0,0 },{ 0,0 } };//for exception

		}

		random_shuffle(directions.begin(), directions.end());//random

		//if Evader is on the left top side and direction result is to go up
		if (pos_row == 0 && pos_col == 0 && directions[i].first == -1)
			directions[i].first += +2;//move down
		else if (pos_row == 0 && pos_col == 0 && directions[i].second == -1)//if direction result is to go left
			directions[i].second += +2;//move right
		//if Evader is on the right top side and direction result is to go up
		if (pos_row == 0 && pos_col == 7 && directions[i].first == -1)
			directions[i].first += +2;//move down
		else if (pos_row == 0 && pos_col == 7 && directions[i].second == +1)//if direction result is to go right
			directions[i].second += -2;//move left
		//if Evader is on the left bottom side and direction result is to go down
		if (pos_row == 7 && pos_col == 0 && directions[i].first == +1)
			directions[i].first += -2;//move up
		else if (pos_row == 7 && pos_col == 0 && directions[i].second == -1)//if direction result is to go left
			directions[i].second += +2;//move right
		//if Evader is on the right bottom side and direction result is to go down
		if (pos_row == 7 && pos_col == 7 && directions[i].first == +1)
			directions[i].first += -2;//move up
		else if (pos_row == 7 && pos_col == 7 && directions[i].second == +1)//if direction result is to go right
			directions[i].second += -2;//move left

		//if Evader is on the top side
		if (pos_row == 0 && pos_col != 0 && pos_col != 7 && directions[i].first == -1) {
			directions = { {+1,0}, {0, +1}, {0,-1} };//prevent for going outside the box
			random_shuffle(directions.begin(), directions.end());	}
		//if Evader is on the left side
		else if (pos_col == 0 && pos_row != 0 && pos_row != 7 && directions[i].second == -1){
			directions = { {+1,0}, {-1,0}, {0,+1} };//prevent for going outside the box
			random_shuffle(directions.begin(), directions.end());	}
		//if Evader is on the bottom side
		else if (pos_row == 7 && pos_col != 0 && pos_col != 7 && directions[i].first == +1) {
			directions = { { -1,0 },{ 0,-1 },{ 0,+1 } };//prevent for going outside the box
			random_shuffle(directions.begin(), directions.end());	}
		//if Evader is on the right side
		else if (pos_col == 7 && pos_row != 0 && pos_row != 7 && directions[i].second == +1) {
			directions = { {+1,0}, { -1,0 },{ 0,-1 } };//prevent for going outside the box
			random_shuffle(directions.begin(), directions.end());
		}


		dr = directions[i].first;//save direction
		dc = directions[i].second;
		new_r = dr + now_row;
		new_c = dc + now_col;

		

		if (new_r >= 0 && new_r < grid_height &&
			new_c >= 0 && new_c < grid_width)
			return directions[i];
		else if(new_r < 0)//for exception
			new_r = new_r +1;
		else if(new_c < 0)//for exception
			new_c = new_c +1;

		directions = {};//init direction

	}
		
	


	

}

