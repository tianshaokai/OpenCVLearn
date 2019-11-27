//
// Created by 小鹏 on 2019-11-27.
//

#include "BitmapMatUtil.h"

BitmapMatUtil::BitmapMatUtil() {

}

BitmapMatUtil::~BitmapMatUtil() {

}

Mat BitmapMatUtil::bitmap2Mat(JNIEnv *env, jobject bitmap) {
    // 1. 获取图片的宽高，以及格式信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    void *pixels;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    Mat mat;
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("nMatToBitmap: CV_8UC4 -> RGBA_8888");
        mat = Mat(info.height, info.width, CV_8UC4, pixels);
    } else {
        LOGE("nMatToBitmap: CV_8UC2 -> RGBA_565");
        mat = Mat(info.height, info.width, CV_8UC2, pixels);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    return mat;
}

void BitmapMatUtil::mat2Bitmap(JNIEnv *env, Mat src, jobject bitmap) {
    // 1. 获取图片的宽高，以及格式信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    void *pixels;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat tmp(info.height, info.width, CV_8UC4, pixels);
        if (src.type() == CV_8UC1) {
            LOGE("nMatToBitmap: CV_8UC1 -> RGBA_8888");
            cvtColor(src, tmp, COLOR_GRAY2RGBA);
        } else if (src.type() == CV_8UC3) {
            LOGE("nMatToBitmap: CV_8UC3 -> RGBA_8888");
            cvtColor(src, tmp, COLOR_RGB2RGBA);
        } else if (src.type() == CV_8UC4) {
            LOGE("nMatToBitmap: CV_8UC4 -> RGBA_8888");
            src.copyTo(tmp);
        }
    } else {
        // info.format == ANDROID_BITMAP_FORMAT_RGB_565
        Mat tmp(info.height, info.width, CV_8UC2, pixels);
        if (src.type() == CV_8UC1) {
            LOGE("nMatToBitmap: CV_8UC1 -> RGB_565");
            cvtColor(src, tmp, COLOR_GRAY2BGR565);
        } else if (src.type() == CV_8UC3) {
            LOGE("nMatToBitmap: CV_8UC3 -> RGB_565");
            cvtColor(src, tmp, COLOR_RGB2BGR565);
        } else if (src.type() == CV_8UC4) {
            LOGE("nMatToBitmap: CV_8UC4 -> RGB_565");
            cvtColor(src, tmp, COLOR_RGBA2BGR565);
        }
    }

    AndroidBitmap_unlockPixels(env, bitmap);
}


