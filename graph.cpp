#include"opengraph.h"
#include<cmath>
using namespace std;
using namespace Gtk;

class Win : public Window
{
public:
	Win() : graph({-5, 5, -3, 6}){
		add(graph);
		graph.add_graph([](float x){return x*x;});
		graph.add_graph([](float x){return sin(x);});
		graph.add_graph([](float x){return x*x*x-2*x+3;});
		graph.add_graph([](float x){return 3*x*x-2;});
		graph.add_graph([](float x){return 3;});
		graph.add_graph([](float x){return sqrt(4-x*x);}, -2, 2);
		graph.add_graph([](float x){return -sqrt(4-x*x);}, -2, 2);
		graph.add_graph([](float x){return log(x);}, 0.001, 6);
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
