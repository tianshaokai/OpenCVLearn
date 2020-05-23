package com.tianshaokai.opencv;

import android.graphics.Bitmap;

public class OpenCVLearn {
    static {
        System.loadLibrary("opencv_learn");
    }

    //变灰处理
    public static native int[] gray(int[] buf, int w, int h);

    public static native int[] blurGaussian(int[] buf, int w, int h);
    public static native int[] blurBoxFilter(int[] buf, int w, int h);
    public static native int[] blurMean(int[] buf, int w, int h);
    public static native int[] blurMedian(int[] buf, int w, int h);
    public static native int[] blurBilateralFilter(int[] buf, int w, int h);

    public static native int[] blur2(int[] buf, int w, int h);


    public static native int faceDetector(Bitmap bitmap, Bitmap.Config argb8888, String path);

    public static native Bitmap faceDetectorResize(Bitmap bitmap, Bitmap.Config argb8888, String path, int width, int height);
}
