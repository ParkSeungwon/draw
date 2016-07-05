#include<array>
#include"opengraph.h"
using namespace std;

OpenGraph::OpenGraph(array<float, 4> range)
{
	width = range[1] - range[0];
	height = range[3] - range[2];
	ranges = range;
	set_size_request(500, 500 * height / width);
}

void OpenGraph::add_graph(function<float(float)> fn)
{
	to_draws.push_back(fn);
}

bool OpenGraph::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	auto alloc = get_allocation();
	int w = alloc.get_width();
	int h = alloc.get_height();
	cr->scale(w/width, h/height);
	cr->set_line_width(2*width/w);
	cr->translate(-ranges[0], ranges[3]);
	cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
	
	cr->save();
	cr->set_source_rgba(0,0,1,0.3);
	cr->move_to(0, ranges[2]);
	cr->line_to(0, ranges[3]);
	cr->move_to(ranges[0], 0);
	cr->line_to(ranges[1], 0);
	cr->stroke();
	cr->restore();

	for(auto& f : to_draws) {
		cr->move_to(ranges[0], f(ranges[0]));
		for(float x = ranges[0] + 0.01; x < ranges[1]; x += 0.01) 
			cr->line_to(x, f(x));
		cr->stroke();
	}
	return true;
}

