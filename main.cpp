#include <iostream>
#include <BmpT.h>
#include <chrono>

using namespace std::chrono;

int main()
{
    std::string path = "C:\\temp\\frameImage_0.bmp";
    BmpPtr grayImg = nullptr, bgrImg = nullptr;

    high_resolution_clock::time_point t0 = high_resolution_clock::now();
    {
        grayImg = BmpT::create(path.c_str(), ImgTypeN::Gray);
    }
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
    {
        bgrImg = BmpT::create(path.c_str(), ImgTypeN::Color);
    }
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

    std::cout << duration_cast<microseconds>(t1 - t0).count() << "\n" << duration_cast<microseconds>(t2 - t1).count();
}