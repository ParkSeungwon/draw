#include"opengraph.h"
#include<cmath>
using namespace std;
using namespace Gtk;

float normal(float x) {
	double sigma = 1;;
	double m = 0;
	return 1/(sigma*sqrt(2*M_PI)) * exp(-(x-m)*(x-m)/(2*sigma*sigma)); 
}

class Win : public Window
{
public:
	Win() : graph({-2, 2, -0.1, 0.5}){
		add(graph);
		graph.add_graph([](float x){return sin(x);});
		graph.add_graph([](float x){return cos(x);});
		graph.add_graph(normal);
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
