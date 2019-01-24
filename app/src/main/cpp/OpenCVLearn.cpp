#include <jni.h>
#include <string>
#include "opencv2/opencv.hpp"
#include "android_log.h"

extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_gray
        (JNIEnv *env, jclass, jintArray buf, jint w, jint h) {
    //获取图片矩阵数组
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    int size = w * h;
    //CV_8UC4--创建--8位无符号的四通道---带透明色的RGB图像
    cv::Mat srcImg(w, h, CV_8UC4, (unsigned char *) srcBuf);
    cv::Mat grayImage;
    cvtColor(srcImg, grayImage, cv::COLOR_BGRA2GRAY);

    cvtColor(grayImage, srcImg, cv::COLOR_GRAY2BGRA);
    //申请整形数组，这个数组可以返回给java使用。注意，这里不能用new或者malloc函数代替。
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);
    return result;
}

extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blur
        (JNIEnv *env, jclass, jintArray buf, jint w, jint h) {
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    cv::Mat srcImg(w, h, CV_8UC4, (unsigned char *) srcBuf);
    cv::Mat temp = srcImg.rowRange(h / 3, 2 * h / 3);
    GaussianBlur(temp, temp, cv::Size(45, 13), 0, 0);
    // 将opencv图片转化成c图片数据，RGBA转化成灰度图4通道颜色数据
    cvtColor(temp, temp, cv::COLOR_RGBA2GRAY, 4);
    int size = w * h;
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);
    return result;
}