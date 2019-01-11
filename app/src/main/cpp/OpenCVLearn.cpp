#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

extern "C"

JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_gray
        (JNIEnv *env, jobject instance, jintArray buf, jint w, jint h) {
    //获取图片矩阵数组
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    int size = w * h;

    Mat srcImg(w, h, CV_8UC4, (unsigned char *) srcBuf);
    Mat grayImage;
    cvtColor(srcImg, grayImage, COLOR_BGRA2GRAY);

    cvtColor(grayImage, srcImg, COLOR_GRAY2BGRA);
    //申请整形数组，这个数组可以返回给java使用。注意，这里不能用new或者malloc函数代替。
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);
    return result;
}
