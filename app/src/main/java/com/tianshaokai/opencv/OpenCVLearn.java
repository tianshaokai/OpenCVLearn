package com.tianshaokai.opencv;

import android.graphics.Bitmap;

public class OpenCVLearn {
    static {
        System.loadLibrary("opencv_learn");
    }

    //变灰处理
    public static native int[] gray(int[] buf, int w, int h);


    public static native int[] blur(int[] buf, int w, int h);

    public static native int[] blur2(int[] buf, int w, int h);


    public static native int faceDetector(Bitmap bitmap, Bitmap.Config argb8888, String path);
//    public static native Bitmap faceDetectorResize(Bitmap bitmap, Bitmap.Config argb8888 , String path,int width,int height);
}
