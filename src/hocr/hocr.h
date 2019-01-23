#include<napi.h>
#include <iostream>
namespace hocr{
    std::string str_hocr(std::string path);
    Napi::String HocrWrapper(const Napi::CallbackInfo &info);
    Napi::Object Init(Napi::Env env,Napi::Object exports);
}