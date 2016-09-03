#include"opengraph.h"
#include<cmath>
using namespace std;
using namespace Gtk;

class Win : public Window
{
public:
	Win() : graph({-1, 9, -1, 14}) { 
		add(graph);
		//graph.add_graph([](float x){return sqrt(x*x*x -3*x + 11);}, -2, 20);
		graph.add_graph([](float x){return sqrt(3)*x;});
		graph.add_graph([](float x){return -sqrt(3)*(x-8);});
		graph.add_graph([](float x){return -1/sqrt(3)*(x-8);});
		graph.add_polar([](float t){return 4;}, 4, 4*sqrt(3));
		//graph.add_graph([](float x){return cos(x);});
		graph.add_text("O", 1, sqrt(3));
		graph.add_text("E", 0, -0.2);
		graph.add_text("F", 8, -0.2);
		show_all_children();

	}

protected:
	OpenGraph graph;
};

int main(int c, char** v)
{
	auto app = Application::create(c, v);
	Win win;
	return app->run(win);
}
