#include<iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
namespace fix_rotate
{
    Mat fix_rotate(char* inputfile);
}