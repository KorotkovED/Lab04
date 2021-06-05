#ifndef HISTOGRAM_H_INCLUDED
#include <vector>
#define HISTOGRAM_H_INCLUDED
#include <string>
#include <iostream>
using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);

void show_histogram_svg(const vector<size_t>& bins);

void svg_end();

void svg_begin(double width, double height);

void svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height,string stroke = "black", string fill = "black");
struct Input;

string make_info_text();
#endif // HISTOGRAM_H_INCLUDED
