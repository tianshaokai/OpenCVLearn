//
// Created by 小鹏 on 2019-11-27.
//

#ifndef OPENCVLEARN_FACEDETECTOR_H
#define OPENCVLEARN_FACEDETECTOR_H

#include <vector>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class FaceDetector {

public:
    //加载文件
    static void loadCascade(const char *fileName);
    //识别矩阵，返回脸的矩形列表
    static vector<Rect> detectorFace(Mat &srcImg);

public:
    FaceDetector();
    ~FaceDetector();
};


#endif //OPENCVLEARN_FACEDETECTOR_H
