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
	void add_graph(std::function<float(float)> fn, float sx, float ex);
	void add_polar(std::function<float(float)> fn, float mv_x = 0, float mv_y = 0);
	void add_text(std::string text, float x, float y);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) ;
	std::array<float, 4> ranges;
	std::vector<std::function<float(float)>> to_draws; 
	std::vector<std::tuple<std::string, float, float>> texts;
	std::vector<std::tuple<std::function<float(float)>, float, float>> polar_draws; 
	std::vector<std::pair<float, float>> xranges;
	float width, height;
};
