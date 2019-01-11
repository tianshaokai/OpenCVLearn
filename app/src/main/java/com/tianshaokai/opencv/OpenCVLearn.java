package com.tianshaokai.opencv;

public class OpenCVLearn {
    static {
        System.loadLibrary("opencv_learn");
//        System.loadLibrary("opencv_java4");
    }

    //变灰处理
    public static native int[] gray(int[] buf, int w, int h);
}
