//
// Created by 小鹏 on 2019-11-27.
//

#include "FaceDetector.h"

FaceDetector::FaceDetector() {


}

FaceDetector::~FaceDetector() {

}

CascadeClassifier cascadeClassifier;

void FaceDetector::loadCascade(const char *fileName) {
    cascadeClassifier.load(fileName);
}

vector<Rect> FaceDetector::detectorFace(Mat &srcImg) {
    //脸的数组
    vector<Rect> faces;
    //用于存放识别到的图像临时矩阵
    Mat temp_mat;
    //灰度图,加快解析速度
    cvtColor(srcImg, temp_mat, COLOR_BGRA2GRAY);
    //直方图均衡化
    equalizeHist(temp_mat, temp_mat);
    //多尺度人脸检测
    cascadeClassifier.detectMultiScale(temp_mat, faces, 1.1, 3, 0, Size(300, 300));
    return faces;
}



