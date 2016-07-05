#pragma once
#include<gtkmm.h>
#include<functional>
#include<vector>
#include<array>

class OpenGraph : public Gtk::DrawingArea
{
public:
	OpenGraph(std::array<float, 4> range);
	void add_graph(std::function<float(float)> fn);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) ;
	std::array<float, 4> ranges;
	std::vector<std::function<float(float)>> to_draws; 
	float width, height;
};
