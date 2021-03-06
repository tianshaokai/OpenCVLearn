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

    srcImg.release();
    grayImage.release();
    return result;
}

extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blurGaussian
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

    cvtColor(srcImg, srcImg, COLOR_RGBA2GRAY, 4);

    int size = w * h;
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);

    return result;
}

extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blurBoxFilter
        (JNIEnv *env, jclass, jintArray buf, jint w, jint h) {
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    Mat srcImg(h, w, CV_8UC4, (unsigned char *) srcBuf);

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
    //使用这个方法，和均值滤波效果一样
    boxFilter(srcImg, srcImg, -1, Size(20, 20));

    cvtColor(srcImg, srcImg, COLOR_RGBA2GRAY, 4);

    int size = w * h;
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);

    return result;
}



extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blurMean
        (JNIEnv *env, jclass, jintArray buf, jint w, jint h) {
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    Mat srcImg(h, w, CV_8UC4, (unsigned char *) srcBuf);

    /**
     * 均值滤波（归一化之后又进行了方框滤波）
     * 第一个参数：输入的图片
     * 第二个参数：输出的图片
     * 第三个参数：核心的大小
     * 第四个参数：锚点的位置，就是我们要进行处理的点，默认值（-1，-1）表示锚点在核的中心
     * 第五个参数：边界模式，默认值BORDER_DEFAULT
     */
    blur(srcImg, srcImg, Size(30, 30));

    cvtColor(srcImg, srcImg, COLOR_RGBA2GRAY, 4);

    int size = w * h;
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);

    return result;
}


extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blurMedian
        (JNIEnv *env, jclass, jintArray buf, jint w, jint h) {
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    Mat srcImg(h, w, CV_8UC4, (unsigned char *) srcBuf);

    /**
     * 中值滤波,孔径范围内的所有像素进行排序，然后取中位数，赋值给核心。
     * 第一个参数：传入的图片
     * 第二个参数：传出的图片
     * 第三个参数：孔径的线性尺寸，必须是大于1的奇数
     */
    medianBlur(srcImg,srcImg,31);

    cvtColor(srcImg, srcImg, COLOR_RGBA2GRAY, 4);

    int size = w * h;
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);
    return result;
}


extern "C" JNIEXPORT jintArray JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_blurBilateralFilter
        (JNIEnv *env, jclass, jintArray buf, jint w, jint h) {
    jint *srcBuf = env->GetIntArrayElements(buf, JNI_FALSE);
    if(srcBuf == NULL) {
        return 0;
    }
    Mat srcImg(h, w, CV_8UC4, (unsigned char *) srcBuf);

    cvtColor(srcImg, srcImg, COLOR_RGBA2RGB);

    /**
     * 双边滤波
     * 第一个参数：传入的图片(必须是CV_8UC1或者CV_8UC3)
     * 第二个参数：传出的图片
     * 第三个参数：每个像素领域的直径
     * 第四个参数：sigmaColor，这个值越大，该像素领域内会有更广的颜色被混合到一起
     * 第五个参数：sigmaSpace，这个值越大，越远的像素会互相影响，第三个参数大于0时，领域的大小和这个值无关，否则成正比
     * 第六个参数：使用默认值BORDER_DEFAULT
     */
    bilateralFilter(srcImg, srcImg, 30, 50, 20);

    cvtColor(srcImg, srcImg, COLOR_RGBA2GRAY, 4);

    int size = w * h;
    //因为new出来的空间还在c中，java是不能直接使用的。
    jintArray result = env->NewIntArray(size);
    //将C的数组拷贝给java中的数组
    env->SetIntArrayRegion(result, 0, size, srcBuf);
    //释放c数组资源
    env->ReleaseIntArrayElements(buf, srcBuf, 0);
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
    srcMat = BitmapMatUtil::bitmapToMat(env, bitmap);//图片源矩阵初始化
    auto faces = FaceDetector::detectorFace(srcMat);//识别图片源矩阵，返回矩形集

    for (Rect faceRect : faces) {// 在人脸部分画矩形
        rectangle(srcMat, faceRect, Scalar(0, 253, 255), 5);//在srcMat上画矩形
        BitmapMatUtil::matToBitmap(env, srcMat, bitmap);// 把mat放回bitmap中
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
    srcMat = BitmapMatUtil::bitmapToMat(env, bitmap);//图片源矩阵初始化
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

extern "C"
JNIEXPORT jobject JNICALL
Java_com_tianshaokai_opencv_OpenCVLearn_getIdCardNumber(JNIEnv *env, jclass clazz, jobject bitmap, jobject argb8888) {

    Mat srcImage = BitmapMatUtil::bitmapToMat(env, bitmap);
    Size fix_size = Size(640, 400);

    resize(srcImage, srcImage, fix_size);

    LOGD("Bitmap 已经成功转换为 Mat, 开始处理图片");

    //灰度化 灰度化处理：图片灰度化处理就是将指定图片每个像素点的RGB三个分量通过一定的算法计算出该像素点的灰度值，使图像只含亮度而不含色彩信息。
    Mat dstGray;
    cvtColor(srcImage, dstGray, COLOR_BGR2GRAY);

    //二值化 二值化：二值化处理就是将经过灰度化处理的图片转换为只包含黑色和白色两种颜色的图像，他们之间没有其他灰度的变化。在二值图中用255便是白色，0表示黑色。
    threshold(dstGray, dstGray, 100, 255, THRESH_BINARY);

    //返回指定形状和尺寸的结构元素
    Mat erodeElement = getStructuringElement(MORPH_RECT, Size(20, 10));
    //腐蚀：减少高亮部分  腐蚀：图片的腐蚀就是将得到的二值图中的黑色块进行放大。即连接图片中相邻黑色像素点的元素。通过腐蚀可以把身份证上的身份证号码连接在一起形成一个矩形区域。
    erode(dstGray, dstGray, erodeElement);
    //膨胀：增加高亮部分
//    dilate(dstGray, dstGray, erodeElement);

    //轮廓检测 轮廊检测：图片经过腐蚀操作后相邻点会连接在一起形成一个大的区域，这个时候通过轮廊检测就可以把每个大的区域找出来，这样就可以定位到身份证上面号码的区域。
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(dstGray, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    Mat result;
    for (int i = 0; i < hierarchy.size(); i++) {
        Rect rect = boundingRect(contours.at(i));
        rectangle(srcImage, rect, Scalar(255, 0, 255));
        // 定义身份证号位置大于图片的一半，并且宽度是高度的6倍以上
        if (rect.y > srcImage.rows / 2 && rect.width / rect.height > 6) {
            result = srcImage(rect);
            break;
        }
    }
    LOGD("图片处理成功，开始返回身份证号图片");
    jobject jobBitmap = BitmapMatUtil::createBitmap(env, result, argb8888);
    result.release();
    dstGray.release();
    srcImage.release();
    return jobBitmap;
}