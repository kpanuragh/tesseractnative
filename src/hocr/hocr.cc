#include "hocr.h"
#include <tesseract/baseapi.h>
#include<stdio.h>
#include "../fix_rotate/fix_rotate.h"
std::string hocr::str_hocr(std::string path)
{
  	char *outText;
	  //Image rotation issue fixing
	Mat im = imread(path);
	Mat gray;
	cvtColor(im, gray, COLOR_BGR2GRAY);
	Mat preprocessed = fix_rotate::preprocess2(gray);
	double skew;
	fix_rotate::hough_transform(preprocessed, im, &skew);
	Mat rotated = fix_rotate::rot(im, skew* CV_PI / 180);	 
	//end rotation issue
cv::cvtColor(rotated, rotated, COLOR_BGR2RGBA); 
	//fix missing pixel
	   int morph_elem = 1;
    int morph_size = 1;
    int morph_operator = 0;
	 Mat origImage = rotated;
	 medianBlur(origImage, origImage,1);
    cvtColor(origImage, origImage, COLOR_RGB2GRAY);
    threshold(origImage, origImage, 0, 255, THRESH_OTSU);

    Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

    morphologyEx(origImage, origImage, MORPH_OPEN, element);

	rotated=origImage;
	//end missing pixel



	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	// // Open input image with leptonica library
	// Pix *image = pixRead(path.c_str());
	cv::cvtColor(rotated, rotated, COLOR_BGR2RGBA); 
	api->SetImage(rotated.data,rotated.cols,rotated.rows, 4, 4*rotated.cols);
	// Get OCR result
	outText = api->GetHOCRText(1);
	//outText=api->GetUTF8Text();

	// Destroy used object and release memory
	api->End();
	
	// pixDestroy(&image);
    return outText;
	delete[] outText;
}
Napi::String hocr::HocrWrapper(const Napi::CallbackInfo &info)
{
    Napi::Env env=info.Env();
    if(info.Length() < 1)
    {
        Napi::TypeError::New(env, "Path Expected").ThrowAsJavaScriptException();
    }
    Napi::String path=info[0].As<Napi::String>();
    return Napi::String::New(env,hocr::str_hocr(path.ToString()));
}
Napi::Object hocr::Init(Napi::Env env,Napi::Object exports)
{
     exports.Set("str_hocr",Napi::Function::New(env,hocr::HocrWrapper));
     return exports;
}