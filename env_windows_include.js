'use strict'

let OPENCV_INCLUDE = ""
if (process.env.OPENCV_INCLUDE) {
    OPENCV_INCLUDE = process.env.OPENCV_INCLUDE
    OPENCV_INCLUDE = OPENCV_INCLUDE.split("\\").join("/")
}
process.stdout.write(OPENCV_INCLUDE)