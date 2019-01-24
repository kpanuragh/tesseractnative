#include "hocr.h"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include<stdio.h>
std::string hocr::str_hocr(std::string path)
{
  	char *outText;

	tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "eng")) {
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	// Open input image with leptonica library
	Pix *image = pixRead(path.c_str());
	api->SetImage(image);
	// Get OCR result
	outText = api->GetHOCRText(1);
	

	// Destroy used object and release memory
	api->End();
	
	pixDestroy(&image);
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