#include <jni.h>
#include <string>
#include "opencv2/opencv.hpp"
#include "android_log.h"
#include "FaceDetector.h"
#include "BitmapMatUtil.h"

using namespace cv;

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
    Mat srcImg(h, w, CV_8UC4, (unsigned char *) srcBuf);
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

extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blur
        (JNIEnv *env, jclass, jintArray buf, jint w, jint h) {
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    Mat srcImg(h, w, CV_8UC4, (unsigned char *) srcBuf);

    /**
    * 高斯滤波
    * 第一个参数：传入的图片
    * 第二个参数：传出的图片
    * 第三个参数：核心（必须是正数和奇数）
    * 第四个参数：sigmaX代表高斯函数在x方向的标准偏差
    * 第五个参数：sigmaY代表高斯函数在Y方向的标准偏差，有默认值为0
    * 第六个参数：边界模式，使用默认值BORDER_DEFAULT
    */
    GaussianBlur(srcImg, srcImg, Size(51, 51), 20, 20);

    /**
      * opencv中方框滤波函数
      * 第一个参数：输入的图片
      * 第二个参数：输出的图片
      * 第三个参数：图片的深度（存储每个像素所用的位数）一般情况使用-1也就是原有的图像深度
      * 第四个参数：核心的大小
      * 第五个参数：锚点的位置，就是我们要进行处理的点，默认值（-1，-1）表示锚点在核的中心
      * 第六个参数：normalize默认值为true，表示内核是否被其区域归一化（normalized）了，当normalize=true的时候，方框滤波就变成了我们熟悉的均值滤波。也就是说，
      *             均值滤波是方框滤波归一化（normalized）后的特殊情况。其中，归一化就是把要处理的量都缩放到一个范围内,比如(0,1)，以便统一处理和直观量化。
      *             而非归一化（Unnormalized）的方框滤波用于计算每个像素邻域内的积分特性，比如密集光流算法（dense optical flow algorithms）
      *             中用到的图像倒数的协方差矩阵（covariance matrices of image derivatives）如果我们要在可变的窗口中计算像素总和，可以使用integral()函数
      * 第七个参数：边界模式，默认值BORDER_DEFAULT
      */
//    boxFilter(srcImg,srcImg,-1, cv::Size(30,30));

    /**
     * 均值滤波（归一化之后又进行了方框滤波）
     * 第一个参数：输入的图片
     * 第二个参数：输出的图片
     * 第三个参数：核心的大小
     * 第四个参数：锚点的位置，就是我们要进行处理的点，默认值（-1，-1）表示锚点在核的中心
     * 第五个参数：边界模式，默认值BORDER_DEFAULT
     */
//    blur(srcImg,srcImg, cv::Size(30,30));

    /**
     * 中值滤波,孔径范围内的所有像素进行排序，然后取中位数，赋值给核心。
     * 第一个参数：传入的图片
     * 第二个参数：传出的图片
     * 第三个参数：孔径的线性尺寸，必须是大于1的奇数
     */
//    medianBlur(srcImg,srcImg,31);


    cvtColor(srcImg, srcImg, COLOR_RGBA2GRAY, 4);
    int size = w * h;
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);

//    jint *pixels = env->GetIntArrayElements(buf, NULL);
//    cv::Mat img(h, w, CV_8UC3, pixels);
//    cv::Mat out(h,w,CV_8UC4);

    /**
    * 双边滤波
    * 第一个参数：传入的图片(必须是CV_8UC1或者CV_8UC3)
    * 第二个参数：传出的图片
    * 第三个参数：每个像素领域的直径
    * 第四个参数：sigmaColor，这个值越大，该像素领域内会有更广的颜色被混合到一起
    * 第五个参数：sigmaSpace，这个值越大，越远的像素会互相影响，第三个参数大于0时，领域的大小和这个值无关，否则成正比
    * 第六个参数：使用默认值BORDER_DEFAULT
    */
//    bilateralFilter(img,out,0,0,0);
//    int size = w * h;
//    jint *re = (jint *) out.data;
//    jintArray result = env->NewIntArray(size);
//    env->SetIntArrayRegion(result, 0, size, re);
//    env->ReleaseIntArrayElements(buf, pixels, 0);

    return result;
}

extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blur2(JNIEnv *env, jclass clazz, jintArray buf, jint w, jint h) {
// 获得图片矩阵数组指针
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if (srcBuf == nullptr) {
        return 0;
    }

    // 根据指针创建一个Mat 四个颜色通道
    Mat imgData(h, w, CV_8UC4, (unsigned char *) srcBuf);

    //变量定义
    Mat src_gray, dst, abs_dst;
    //使用高斯滤波消除噪声
    GaussianBlur(imgData, imgData, Size(3, 3), 0, 0, BORDER_DEFAULT);
    //转换为灰度图
    cvtColor(imgData, src_gray, COLOR_RGBA2GRAY);
    //使用Laplace函数
    Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    //计算绝对值
    convertScaleAbs(dst, abs_dst);

    // 恢复格式
    //cvtColor(abs_dst, imgData, COLOR_GRAY2BGRA);

    Mat dstResult;
    //将dstImage内所有元素为0
    dstResult = Scalar::all(0);

    //使用Laplacian算子输出的边缘图，abs_dst作为掩码，来将原图imgData拷贝到目标图dstResult中
    imgData.copyTo(dstResult, abs_dst);

    int size = w * h;

    jint *re = (jint *) dstResult.data;

    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, re);
    env->ReleaseIntArrayElements(buf, srcBuf, 0);
    return result;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_faceDetector(JNIEnv *env, jclass clazz, jobject bitmap,
                                                     jobject argb8888, jstring _path) {
    const char *path = env->GetStringUTFChars(_path, 0);//文件路径
    FaceDetector::loadCascade(path);//加载文件

    Mat srcMat;//图片源矩阵
    srcMat = BitmapMatUtil::bitmap2Mat(env, bitmap);//图片源矩阵初始化
    auto faces = FaceDetector::detectorFace(srcMat);//识别图片源矩阵，返回矩形集

    for (Rect faceRect : faces) {// 在人脸部分画矩形
        rectangle(srcMat, faceRect, Scalar(0, 253, 255), 5);//在srcMat上画矩形
        BitmapMatUtil::mat2Bitmap(env, srcMat, bitmap);// 把mat放回bitmap中
    }
    env->ReleaseStringUTFChars(_path, path);//释放指针
    return faces.size();//返回尺寸
}

extern "C" JNIEXPORT jobject JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_faceDetectorResize(JNIEnv *env, jclass clazz,
                                                           jobject bitmap, jobject argb8888,
                                                           jstring path_, jint width, jint height) {
    const char *path = env->GetStringUTFChars(path_, 0);//文件路径
    FaceDetector::loadCascade(path);//加载文件

    Mat srcMat;//图片源矩阵
    srcMat = BitmapMatUtil::bitmap2Mat(env, bitmap);//图片源矩阵初始化
    auto faces = FaceDetector::detectorFace(srcMat);//识别图片源矩阵，返回矩形集
    Rect faceRect = faces[0];
    rectangle(srcMat, faceRect, Scalar(0, 253, 255), 5);//在srcMat上画矩形
    //识别目标区域区域---------------------------
    Rect zone;
    int w = faceRect.width;//宽
    int h = faceRect.height;//高
    int offSetLeft = w / 4;//x偏移
    int offSetTop = static_cast<int>(h * 0.5);
    zone.x = faceRect.x - offSetLeft;
    zone.y = faceRect.y - offSetTop;
    zone.width = w / 4 * 2 + w;
    zone.height = static_cast<int>(zone.width * (height * 1.0 / width));
    rectangle(srcMat, zone, Scalar(253, 95, 47), 5);//在srcMat上画矩形

    env->ReleaseStringUTFChars(path_, path);//释放指针

    resize(srcMat(zone), srcMat, Size(width, height));//<----重定义尺寸

    return BitmapMatUtil::createBitmap(env, srcMat, argb8888);//返回图片
}