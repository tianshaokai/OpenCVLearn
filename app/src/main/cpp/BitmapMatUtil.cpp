//
// Created by 小鹏 on 2019-11-27.
//

#include "BitmapMatUtil.h"

BitmapMatUtil::BitmapMatUtil() {

}

BitmapMatUtil::~BitmapMatUtil() {

}

Mat BitmapMatUtil::bitmapToMat(JNIEnv *env, jobject bitmap) {
    // 1. 获取图片的宽高，以及格式信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    void *pixels;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);
    Mat mat;
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGD("nMatToBitmap: CV_8UC4 -> RGBA_8888");
        mat = Mat(info.height, info.width, CV_8UC4, pixels);
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        LOGD("nMatToBitmap: CV_8UC2 -> RGBA_565");
        mat = Mat(info.height, info.width, CV_8UC2, pixels);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    return mat;
}

int BitmapMatUtil::matToBitmap(JNIEnv *env, Mat &mat, jobject bitmap) {
    // 1. 获取图片的宽高，以及格式信息
    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    void *pixels;
    AndroidBitmap_lockPixels(env, bitmap, &pixels);
    LOGD("开始Mat 转换为 bitmap 宽度: %d, 高度: %d", mat.cols, mat.rows);

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Mat tmp(info.height, info.width, CV_8UC4, pixels);
        if (mat.type() == CV_8UC1) {
            cvtColor(mat, tmp, COLOR_GRAY2RGBA);
        } else if (mat.type() == CV_8UC2) {
            cvtColor(mat, tmp, COLOR_BGR5652BGRA);
        } else if (mat.type() == CV_8UC4) {
            mat.copyTo(tmp);
        }
    } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565) {
        Mat tmp(info.height, info.width, CV_8UC2, pixels);
        if (mat.type() == CV_8UC1) {
            cvtColor(mat, tmp, COLOR_GRAY2BGR565);
        } else if (mat.type() == CV_8UC2) {
            mat.copyTo(tmp);
        } else if (mat.type() == CV_8UC4) {
            cvtColor(mat, tmp, COLOR_RGBA2BGR565);
        }
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    return 0;
}

jobject BitmapMatUtil::createBitmap(JNIEnv *env, Mat &mat, jobject config) {
    jclass java_bitmap_class = (jclass) env->FindClass("android/graphics/Bitmap");//类名
    jmethodID mid = env->GetStaticMethodID(java_bitmap_class, "createBitmap",//获取方法
                                           "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");
    jobject bitmap = env->CallStaticObjectMethod(java_bitmap_class, mid, mat.cols, mat.rows,
                                                 config);
    matToBitmap(env, mat, bitmap);
    return bitmap;
}


