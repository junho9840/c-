#include "Graph.h"
#include "Simple_window.h"
#include "Character.h"

using namespace Graph_lib;

int main()
{
	srand(time(nullptr));

	Point tl(100, 100);
	Simple_window win(tl, 800, 800, "Chasing");

	vector<Character*> characters;

	Pursuer* stoker = new Pursuer(&win, 3, 0);//Dynamically Create Character 
	Evader* escaper = new Evader(&win, 4, 7);

	stoker->setEnemy(escaper);//setting enemy
	escaper->setEnemy(stoker);


	characters.push_back(stoker);//put back in Character Vector
	characters.push_back(escaper);

	Graph_lib::Text t1(Point(350, 400), "The end");//Create "The End" text
	t1.set_font_size(40);

	do
	{
		win.wait_for_button();

		for (Character* ch : characters)
		{
			ch->move();
		}
		if (stoker->row() == escaper->row() && stoker->col() == escaper->col())//if Pursuer catch Evader
			break;
	} while (true);
	win.attach(t1);//print "The End"

	win.wait_for_button();

	exit;
}
