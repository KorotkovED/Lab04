#include "histogram.h"

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
void show_histogram_svg(const vector<size_t>& bins)
{

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    const size_t MAX_ASTERISK = IMAGE_HEIGHT - TEXT_BASELINE * 2;
     size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    svg_begin( 300, 400);
    for (size_t bin : bins)
    {
       size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }
        const double bin_width = BIN_HEIGHT * bin;
        svg_text(top + BIN_HEIGHT, TEXT_BASELINE , to_string(bin));
        svg_rect(top + TEXT_LEFT, TEXT_BASELINE * 2, BIN_HEIGHT, bin_width, "black", "blue");
        top += BIN_HEIGHT ;
    }
    svg_end();
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



