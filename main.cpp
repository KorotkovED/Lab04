#include <iostream>
#include <vector>
#include <iomanip>
#include "histogram.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <math.h>


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
Input read_input(istream& in, bool F)
{

    Input data;

    if (F) cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (F) cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (F) cerr << "Enter bin count: ";
    in >> data.bin_count;

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



vector<size_t> make_histogram(Input data)
{
    size_t number_count=data.numbers.size();
    vector<size_t> bins(data.bin_count);

    cerr<< "cerr "<<data.bin_count;
    double min, max;
    find_minmax(data.numbers, min, max);
    double bin_size = (max - min) / data.bin_count;
    for (size_t i = 0; i < number_count; i++)
    {

        bool found = false;
        for (size_t j = 0; (j < data.bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= data.numbers[i]) && (data.numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
// ���� �� numbers �� ����������!

        if (!found)
        {
            bins[data.bin_count - 1]++;
        }

    } // ����� ����� �� numbers

    return bins;
}
Input
download(const string& address)
{
    stringstream buffer;
    const char* line;

    CURL* curl = curl_easy_init();
    curl_version_info_data *curl_version_info(CURLversion stamp);


    curl_global_init(CURL_GLOBAL_ALL);


    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        cerr<< "cURL Version: " <<curl_version_info(CURLVERSION_NOW)<<endl;
        auto info = curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_VERSION_SSL);
        cerr<<"SSL version "<<info;

        res = curl_easy_perform(curl);
        if (res != 0)
        {
            cerr<< "curl_easy_perform() failed: %s\n"<< curl_easy_strerror(res);
            exit(1);
        }
        curl_easy_cleanup(curl);
    }


    return read_input(buffer, false);
}


size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{


    auto data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

    buffer->write(reinterpret_cast<const char*>(items), data_size);

    return (data_size);
}
BOOL GetComputerNameA(
    LPSTR   lpBuffer,
    LPDWORD lpnSize
);
string make_info_text()
{
    stringstream buffer;
    // TODO: �������� ������ �������, �������� � �����.
    DWORD WINAPI GetVersion(void);
    DWORD info = 0;
    info = GetVersion();
    printf("n = %08x\n",info); //16
    printf("%u ", info);//10
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    cerr << " "<<version<<endl;
    DWORD mask1 = 0x0000ffff;
    DWORD platform = info >> 16;

    DWORD maskVision = 0b00000000'11111111;
    DWORD version_major = version & maskVision;
    DWORD mask2 = 0x0000ffff;
    DWORD version_minor = version >> 8;
    if ((info & 0x1000ffff) == 0)
    {
        version_major = 0;
    }
    DWORD build = platform;

   printf("Wndows v.%u.%u(build %u)\n", version_major, version_minor,build);

    //TODO:
    LPSTR   x;
    LPDWORD y;
            char system_dir[MAX_PATH];
    GetSystemDirectory(system_dir, MAX_PATH);
    printf("System directory: %s", system_dir);
    auto huffer = GetComputerNameA(x,y);
    printf(" Computer name:  " , huffer);
    return buffer.str();
}

int main(int argc, char* argv[])
{
    Input input;
    if(argc>1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin,true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
    return 0;
}
