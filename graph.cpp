#include"opengraph.h"
#include<cmath>
using namespace std;
using namespace Gtk;

class Win : public Window
{
public:
	Win() : graph({-3, 3, -1, 6}){
		add(graph);
		graph.add_graph([](float x){return x*x;});
		graph.add_graph([](float x){return sin(x);});
		graph.add_graph([](float x){return x*x*x-2*x+3;});
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
