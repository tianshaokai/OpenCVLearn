package com.tianshaokai.opencv;

public class OpenCVLearn {
    static {
        System.loadLibrary("opencv_learn");
    }

    public native void ocrCar(String image);
}
