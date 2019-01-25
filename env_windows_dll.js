'use strict'

let OPENCV_DLL = ""
if (process.env.OPENCV_DLL) {
    OPENCV_DLL = process.env.OPENCV_DLL+"\\opencv_world401.dll";
    OPENCV_DLL = OPENCV_DLL.split("\\").join("/")
}
process.stdout.write(OPENCV_DLL)