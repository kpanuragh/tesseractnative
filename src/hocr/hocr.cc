#include "hocr.h"
#include <tesseract/baseapi.h>
#include<stdio.h>
#include <cstring>
#include <string>
#include "../skew_fix/skew_fix.h"
#include "../fix_rotate/fix_rotate.h"
std::string hocr::str_hocr(std::string path)
{
	try{
  	char *outText;
	  //Image rotation issue fixing
	char *path_char = new char[path.length() + 1]; 
	std::strcpy(path_char, path.c_str());

	Mat im = fix_rotate::fix_rotate(path_char);

	cvtColor(im,im,COLOR_GRAY2RGB);
	fastNlMeansDenoisingColored(im,im);
	Mat gray;

	cvtColor(im, gray, COLOR_BGR2GRAY);
	Mat preprocessed = skew_fix::preprocess1(gray);

	preprocessed = skew_fix::preprocess1(preprocessed);

	double skew;
	skew_fix::hough_transform(preprocessed, im, &skew);
	
	Mat rotated = skew_fix::rot(im, skew* CV_PI / 180);	 
	
	//end rotation issue
// cv::cvtColor(rotated, rotated, COLOR_BGR2RGBA); 
// 	//fix missing pixel
// 	   int morph_elem = 1;
//     int morph_size = 1;
//     int morph_operator = 0;
// 	 Mat origImage = rotated;
// 	 medianBlur(origImage, origImage,5);
//     cvtColor(origImage, origImage, COLOR_RGB2GRAY);
//     threshold(origImage, origImage, 0, 255, THRESH_OTSU);

//     Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

//     morphologyEx(origImage, origImage, MORPH_OPEN, element);

// 	rotated=origImage;
// 	//end missing pixel
rotated=im;


	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	// // Open input image with leptonica library
	// Pix *image = pixRead(path.c_str());
	cv::cvtColor(rotated, rotated, COLOR_BGR2RGBA); 
	cv::imwrite(path,rotated);
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
		catch(cv::Exception& e){
		  const char* err_msg = e.what();
    	std::cout << "exception caught: " << err_msg << std::endl;
	}
}
Napi::String hocr::HocrWrapper(const Napi::CallbackInfo &info)
{
	try{
    Napi::Env env=info.Env();
    if(info.Length() < 1)
    {
        Napi::TypeError::New(env, "Path Expected").ThrowAsJavaScriptException();
    }
    Napi::String path=info[0].As<Napi::String>();
    return Napi::String::New(env,hocr::str_hocr(path.ToString()));
	}	catch(cv::Exception& e){
		  const char* err_msg = e.what();
    	std::cout << "exception caught: " << err_msg << std::endl;
	}
}
Napi::Object hocr::Init(Napi::Env env,Napi::Object exports)
{
	
     exports.Set("str_hocr",Napi::Function::New(env,hocr::HocrWrapper));
     return exports;
}