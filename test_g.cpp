#include <iostream>
#include "sp_graphics.hpp"

using namespace std;
using namespace sp;

int main() {
	
	graphics g;
	graphics g2;
	input ip;

	graphics::color red = {1.0f, 0.0f, 0.0f, 1.0f};
	graphics::color blue = {0.0f, 0.0f, 1.0f, 1.0f};
	
	while(true)
	{
		ip.capture(g.get_handle());

		if(ip.shouldquit)
			break;



		g.begin();
		g.clear_color(red);
		g.end();

		g2.begin();
		g.clear_color(blue);
		g2.end();



	}


	return 0;
}