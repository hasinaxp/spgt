#include "spgt/sp_graphics.hpp"

using namespace sp;

int main()
{
	graphics g;
	g.clear_color(colorcode::CerulianBlue);
	input ip;

	pen2d pen;

	cout << g.wnd->width << " " << g.wnd->height << endl;
	while(true)
	{
		//user input 
		ip.capture(g.get_handle());
		if(ip.shouldquit)
			break;

		

		//drawing logic
		g.begin();
		
		//pen.origin = PEN_ORIGIN_TOPLEFT;
		pen.canvas = PEN_CANVAS_TOPLEFT;
		pen.pen_down(g.wnd->width, g.wnd->height);
		pen.thickness = 1.0;
		pen.fillcolor = colorcode::Lime;
		pen.fill_rect({0, 0, 200, 200});
		pen.draw_rect({0, 0, 200, 200});
		pen.fillcolor = colorcode::Red;
		pen.fill_rect({0, 100, 4, 4});
		pen.fill_rect({0, -100, 4, 4});
		pen.fill_rect({-100, 0, 4, 4});
		pen.fill_rect({100, 0, 4, 4});

		pen.draw_line({-100, 0}, {100, 0});
		pen.draw_line({0, -100}, {0, 100});

		pen.thickness = 1.0;
		pen.draw_circle({0, 0}, 100 );
		pen.fillcolor = colorcode::Brown;
		//pen.draw_text({8,-8}, "hello world nice to meet you all I am spandan > 3 <", {194,194});

		pen.pen_up();
		g.end();
	}

}


