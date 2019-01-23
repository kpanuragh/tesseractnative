#include <napi.h>
#include "hocr/hocr.h"
Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	return hocr::Init(env,exports);
}

NODE_API_MODULE(tessractnative, InitAll)