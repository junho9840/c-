#include "Graph.h"
#include "Simple_window.h"
#include "Character.h"

using namespace Graph_lib;


int main()
{
	Point tl(100, 100);
	Simple_window win(tl, 800, 800, "Box");

	
	Graph_lib::Box r1(Point(400, 400), 100, 100, 25); //top left point, width, height, radius
	r1.set_color(Color::red);
	Graph_lib::Box r2(Point(200, 200), 200, 100, 15); //top left point, width, height, radius
	r2.set_style(Line_style::dash);
	r2.set_color(Color::yellow);
	Graph_lib::Box r3(Point(150, 600), 350, 100, 5); //top left point, width, height, radius
	r3.set_style(Line_style::dot);
	
	win.attach(r1);
	win.attach(r2);
	win.attach(r3);

	win.wait_for_button();

	win.detach(r1);
	win.detach(r2);
	win.detach(r3);

	win.set_label("Regular Polygon");

	Graph_lib::Regular_polygon r4(Point(400, 400), 7, 100);//Center point, number of side, radius
	r4.set_color(Color::blue);
	Graph_lib::Regular_polygon r5(Point(100, 100), 5, 50);//Center point, number of side, radius
	r5.set_style(Line_style::dot);
	Graph_lib::Regular_polygon r6(Point(250, 150), 3, 150);//Center point, number of side, radius
	r6.set_color(Color::yellow);
	r6.set_style(Line_style::solid);


	win.attach(r4);
	win.attach(r5);
	win.attach(r6);

	win.wait_for_button();

	win.detach(r4);
	win.detach(r5);
	win.detach(r6);

	win.set_label("Star");
	
	Graph_lib::Star r7(Point(400, 400), 5, 50, 100);//center,number of sides, radius1, radius2
	r7.set_color(Color::red);
	Graph_lib::Star r8(Point(200, 200), 100, 50, 100);//center,number of sides, radius1, radius2
	r8.set_style(Line_style::dot);
	Graph_lib::Star r9(Point(600, 300), 50, 50, 100);//center,number of sides, radius1, radius2
	r9.set_color(Color::blue);
	r9.set_style(Line_style::dashdotdot);


	win.attach(r7);
	win.attach(r8);
	win.attach(r9);

	win.wait_for_button();

	win.detach(r7);
	win.detach(r8);
	win.detach(r9);
	


}
