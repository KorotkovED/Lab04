#ifndef HISTOGRAM_H_INCLUDED
#include <vector>
#include <string>
#include <Windows.h>
#define HISTOGRAM_H_INCLUDED
using namespace std;
struct Inputp
{
      DWORD build;
       DWORD version_major;
       DWORD version_minor;
       TCHAR bufferrr[MAX_COMPUTERNAME_LENGTH + 1];
};
struct Input {  vector<double> numbers; size_t bin_count;};
void find_minmax(const vector<double>& numbers, double& min, double& max);
Inputp
make_info_text();
void show_histogram_svg(const vector<size_t>& bins);

void svg_end();

void svg_begin(double width, double height);

void svg_text(double left, double baseline, string text);

void svg_rect(double x, double y, double width, double height,string stroke = "black", string fill = "black");
#endif // HISTOGRAM_H_INCLUDED
