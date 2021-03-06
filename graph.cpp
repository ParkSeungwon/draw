#include"opengraph.h"
#include<cmath>
using namespace std;
using namespace Gtk;

class Win : public Window
{
public:
	Win() : graph({0, 0.5, 0, 0.5}){
		add(graph);
		//graph.add_graph([](float x){return sqrt(x*x*x -3*x + 11);}, -2, 20);
		//graph.add_polar([](float t){return (1-cos(t));});
		//graph.add_polar([](float t){return 1;}, 3, 0.3);
		//graph.add_graph([](float x){return cos(x);});
		graph.add_graph([](float x){return abs(log(1/(1-x))-x);});
		graph.add_graph([](float x){return 2*x*x;});
		graph.add_text("cosx, circle", 2, 1);
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
