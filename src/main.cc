#include <napi.h>
#include "hocr/hocr.h"
#include <opencv2/opencv.hpp>
using namespace cv;
Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	return hocr::Init(env,exports);
}

NODE_API_MODULE(tessractnative, InitAll)