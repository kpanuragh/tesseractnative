#include<napi.h>
#include <iostream>
#include <opencv2/opencv.hpp>
namespace hocr{
    std::string str_hocr(std::string path);
    Napi::String HocrWrapper(const Napi::CallbackInfo &info);
    Napi::Object Init(Napi::Env env,Napi::Object exports);
    void hough_transform(cv::Mat& im, cv::Mat& orig, double* skew);
    cv::Mat preprocess1(cv::Mat& im);
    cv::Mat preprocess2(cv::Mat& im);
    cv::Mat rot(cv::Mat& im, double thetaRad);
}