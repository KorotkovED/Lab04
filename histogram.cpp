#include "histogram.h"
#include <iomanip>
#include <iostream>
#include <string>
void find_minmax(const vector<double>& numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
}
void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout <<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}
void svg_end()
{
    cout << "</svg>\n";
}

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left <<"' y='"<<baseline<<"' >"<<text<<"</text>";
}
void show_histogram_svg(const vector<size_t>& bins)
{
    const auto IMAGE_WIDTH = 600;
    const auto IMAGE_HEIGHT = 500;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    const size_t MAX_ASTERISK = IMAGE_HEIGHT - 20;
     size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count*BIN_HEIGHT > MAX_ASTERISK;
    svg_begin( 500, 600);
    for (size_t bin : bins)
    {
       size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / (max_count*BIN_HEIGHT);
            height = (size_t)(bin * scaling_factor);
        }
        const double bin_width = BIN_HEIGHT * height;
        svg_text(top + BIN_HEIGHT, TEXT_BASELINE , to_string(bin));
        svg_rect(top + TEXT_LEFT, TEXT_BASELINE *2 , BIN_HEIGHT, bin_width, "black", "blue");
        top += BIN_HEIGHT ;
    }
string w = "Windows v.";
string p = " .";
string b ="[build ";
string a = " ]";
string c = "Computer name: ";
make_info_text();
Inputp i;
 svg_text(top + BIN_HEIGHT, TEXT_BASELINE + 75 , w);
 svg_text(top + BIN_HEIGHT + 80, TEXT_BASELINE +75 ,to_string(i.version_minor));
  svg_text(top + BIN_HEIGHT + 90, TEXT_BASELINE +75 , p);
 svg_text(top + BIN_HEIGHT + 95, TEXT_BASELINE +75  , to_string(i.version_major));
 svg_text(top + BIN_HEIGHT + 120, TEXT_BASELINE+75 , b);
 svg_text(top + BIN_HEIGHT + 160, TEXT_BASELINE+75 , to_string(i.build));
 svg_text(top + BIN_HEIGHT + 230, TEXT_BASELINE + 75, a);
  svg_text(top + BIN_HEIGHT, TEXT_BASELINE +100 , c);
 svg_text(top + BIN_HEIGHT + 115, TEXT_BASELINE +100, to_string(i.bufferrr[MAX_COMPUTERNAME_LENGTH + 1]) );

    svg_end();
}


