#include<iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
namespace skew_fix{
void hough_transform(Mat& im, Mat& orig, double* skew);
Mat preprocess1(Mat& im);
Mat preprocess2(Mat& im);
Mat rot(Mat& im, double thetaRad);

}
