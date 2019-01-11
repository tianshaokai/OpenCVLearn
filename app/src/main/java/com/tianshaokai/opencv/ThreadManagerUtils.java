package com.tianshaokai.opencv;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadManagerUtils {

    private static ExecutorService executorService = null;

    private ThreadManagerUtils() { }

    public static ExecutorService getSingleThread() {
        if (executorService == null) {
            executorService = Executors.newSingleThreadExecutor();
        }
        return executorService;
    }



}
