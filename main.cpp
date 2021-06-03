#include <iostream>
#include <vector>
#include <iomanip>
#include "histogram.h"
#include <curl/curl.h>



using namespace std;
vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

struct Input {
    vector<double> numbers;
    size_t bin_count;
     bool prompt;
};
Input
read_input(istream& in, bool prompt) {
    Input data;
    if (prompt == true){
    cerr << "Enter number count: ";}
    size_t number_count;
    in >> number_count;
   if (prompt == true){
    cerr << "Enter numbers: ";}
    data.numbers = input_numbers(in, number_count);

    size_t bin_count;
    if (prompt == true){
    cerr << "Enter column count: ";}
    cin >> bin_count;
    return data;
}
void show_histogram_text(const vector<size_t>& bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins)
    {
        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++)
        {
            cout << '*';
        }
        cout << '\n';
    }
}




int make_histogram(vector<double> numbers ,size_t bin_count, vector<size_t>& bins)
{
    double min, max;
    find_minmax(numbers, min, max);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
}

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
   Input data= read_input(cin, true);
 vector<size_t> bins(data.bin_count);
    make_histogram(data.numbers,data.bin_count, bins);
    show_histogram_svg(bins);
    return 0;
}
