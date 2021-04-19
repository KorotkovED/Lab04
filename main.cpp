#include <iostream>
#include <vector>
#include <iomanip>


using namespace std;
  void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
  }
  void svg_end() {
    cout << "</svg>\n";
}
void show_histogram_svg(const vector<size_t>& bins)
{
    size_t width;
        svg_begin( 300, 400);
        svg_end();

}

void show_histogram_text(const vector<size_t>& bins)
{
 const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }
}

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

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

int make_histogram(const vector<double>& numbers, size_t bin_count, vector<size_t>& bins)
{
double min, max;
find_minmax(numbers, min, max);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
}

int main() {
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
const auto numbers = input_numbers(number_count);


    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;
    vector<size_t> bins(bin_count);
make_histogram(numbers, bin_count, bins);
for ( int i = 0; i< bin_count; i++)
{
    cout<<" "<< bins[i]<<endl;
}
show_histogram_svg(bins);
    return 0;
}
