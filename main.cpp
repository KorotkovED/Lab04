#include <iostream>
#include <vector>
#include <iomanip>
#include "histogram.h"
#include <curl/curl.h>
#include <sstream>
#include <string>



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
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    TODO:
    size_t data_size = item_size * item_count;
 stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
 (*buffer).write(reinterpret_cast<char*>(&items), data_size);
     return 0;
}
Input
download(const string& address) {
    stringstream buffer;

 TODO:  CURL *curl = curl_easy_init();
if(curl) {
  CURLcode res;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
  res = curl_easy_perform(curl);
  if(res != 0)
  {
    const char *curl_easy_strerror(CURLcode errornum);
    exit(1);

  }
  curl_easy_cleanup(curl);
}

    return read_input(buffer, false);
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

int main(int argc, char* argv[])
{Input data;
    curl_global_init(CURL_GLOBAL_ALL);
    if (argc > 1)
    {
  Input input = download(argv[1]);
}
else{
   data = read_input(cin, true);
}

 vector<size_t> bins(data.bin_count);
    make_histogram(data.numbers,data.bin_count, bins);
    show_histogram_svg(bins);
    return 0;
}
