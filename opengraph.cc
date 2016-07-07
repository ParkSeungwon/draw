#include"opengraph.h"
using namespace std;

OpenGraph::OpenGraph(array<float, 4> range)
{
	width = range[1] - range[0];
	height = range[3] - range[2];
	ranges = range;
	set_size_request(700, 700 * height / width);
}

void OpenGraph::add_graph(function<float(float)> fn)
{
	to_draws.push_back(fn);
	xranges.push_back({ranges[0], ranges[1]});
}

void OpenGraph::add_graph(function<float(float)> fn, float sx, float ex)
{
	to_draws.push_back(fn);
	xranges.push_back({sx, ex});
}

bool OpenGraph::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	auto alloc = get_allocation();
	int w = alloc.get_width();
	int h = alloc.get_height();
	cr->scale(w/width, h/height);
	float step = width / w;
	cr->set_line_width(2 * step);
	cr->translate(-ranges[0], ranges[3]);
	cr->transform(Cairo::Matrix(1,0,0,-1,0,0));

	//Axis drawing 	
	cr->save();
	cr->set_source_rgba(0,0,1,0.3);
	cr->move_to(0, ranges[2]);
	cr->line_to(0, ranges[3]);
	cr->move_to(ranges[0], 0);
	cr->line_to(ranges[1], 0);
	cr->stroke();
	float ruler;
	for(ruler = 0.1; ruler < step * 50; ruler *= 10);
	cr->set_font_size(step * 20);
	for(float x = 0; x > ranges[0]; x -= ruler) {
		cr->move_to(x, 0);
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
		cr->show_text('|' + to_string(x).erase(4));
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
	}
	for(float x = ruler; x < ranges[1]; x += ruler) {
		cr->move_to(x, 0);
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
		cr->show_text('|' + to_string(x).erase(4));
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
	}
	for(float y = -ruler; y > ranges[2]; y -= ruler) {
		cr->move_to(0, y);
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
		cr->show_text('_' + to_string(y).erase(4));
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
	}
	for(float y = ruler; y < ranges[3]; y += ruler) {
		cr->move_to(0, y);
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
		cr->show_text('_' + to_string(y).erase(4));
		cr->transform(Cairo::Matrix(1,0,0,-1,0,0));
	}
	cr->restore();

	//graph drawing
	for(int i=0; i<to_draws.size(); i++) {
		cr->move_to(xranges[i].first, to_draws[i](xranges[i].first));
		for(float x = xranges[i].first + step; x < xranges[i].second; x += step) 
			cr->line_to(x, to_draws[i](x));
		cr->stroke();
	}
	return true;
}

