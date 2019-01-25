'use strict'

let OPENCV_LIB = ""
if (process.env.OPENCV_LIB) {
    OPENCV_LIB = process.env.OPENCV_LIB+"\\opencv_world401.lib";
    OPENCV_LIB = OPENCV_LIB.split("\\").join("/")
}
process.stdout.write(OPENCV_LIB)