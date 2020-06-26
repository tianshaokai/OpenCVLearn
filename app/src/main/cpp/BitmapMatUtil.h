//
// Created by 小鹏 on 2019-11-27.
//

#ifndef OPENCVLEARN_BITMAPMATUTIL_H
#define OPENCVLEARN_BITMAPMATUTIL_H

#include <android/bitmap.h>
#include "android_log.h"
#include "opencv2/opencv.hpp"

using namespace cv;


class BitmapMatUtil {

public:
    static Mat bitmapToMat(JNIEnv *env, jobject bitmap);

    static int matToBitmap(JNIEnv *env, Mat &mat, jobject bitmap);

    static jobject createBitmap(JNIEnv *env, Mat &mat, jobject config);

public:
    BitmapMatUtil();
    ~BitmapMatUtil();
};


#endif //OPENCVLEARN_BITMAPMATUTIL_H
