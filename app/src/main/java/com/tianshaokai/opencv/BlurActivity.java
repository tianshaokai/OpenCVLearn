package com.tianshaokai.opencv;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class BlurActivity extends AppCompatActivity {

    private static final String TAG = "BlurActivity";
    private ImageView ivImage1, ivImage2;

    private Button button1,button2,button3,button4,button5;

    private Bitmap bitmap;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_blur);

        ivImage1 = findViewById(R.id.ivImage1);
        ivImage2 = findViewById(R.id.ivImage2);

        button1 = findViewById(R.id.button1);
        button2 = findViewById(R.id.button2);
        button3 = findViewById(R.id.button3);
        button4 = findViewById(R.id.button4);
        button5 = findViewById(R.id.button5);

        ThreadManagerUtils.getSingleThread().execute(() -> {
            bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.image1);
            MainThread.run(() -> ivImage1.setImageBitmap(bitmap));

            blurGaussian();
        });

        button1.setOnClickListener(onClickListener);
        button2.setOnClickListener(onClickListener);
        button3.setOnClickListener(onClickListener);
        button4.setOnClickListener(onClickListener);
        button5.setOnClickListener(onClickListener);
    }

    private View.OnClickListener onClickListener = v -> {
        switch (v.getId()) {
            case R.id.button1:
                ThreadManagerUtils.getSingleThread().execute(this::blurGaussian);
                break;

            case R.id.button2:
                ThreadManagerUtils.getSingleThread().execute(this::blurBoxFilter);
                break;

            case R.id.button3:
                ThreadManagerUtils.getSingleThread().execute(this::blur);
                break;

            case R.id.button4:
                ThreadManagerUtils.getSingleThread().execute(this::blurMedian);
                break;

            case R.id.button5:
                ThreadManagerUtils.getSingleThread().execute(this::blurBilateralFilter);
                break;
        }
    };

    private void blurGaussian() {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

        int[] resultPixes = OpenCVLearn.blurGaussian(pixels, width, height);
        final Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        resultBitmap.setPixels(resultPixes, 0, width, 0, 0, width, height);

        MainThread.run(() -> ivImage2.setImageBitmap(resultBitmap));
    }

    private void blurBoxFilter() {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

        int[] resultPixes = OpenCVLearn.blurBoxFilter(pixels, width, height);
        final Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        resultBitmap.setPixels(resultPixes, 0, width, 0, 0, width, height);

        MainThread.run(() -> ivImage2.setImageBitmap(resultBitmap));
    }


    private void blur() {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

        int[] resultPixes = OpenCVLearn.blur(pixels, width, height);
        final Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        resultBitmap.setPixels(resultPixes, 0, width, 0, 0, width, height);

        MainThread.run(() -> ivImage2.setImageBitmap(resultBitmap));
    }

    private void blurMedian() {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

        int[] resultPixes = OpenCVLearn.blurMedian(pixels, width, height);
        final Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        resultBitmap.setPixels(resultPixes, 0, width, 0, 0, width, height);

        MainThread.run(() -> ivImage2.setImageBitmap(resultBitmap));
    }

    private void blurBilateralFilter() {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();

        int[] pixels = new int[width * height];
        bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

        int[] resultPixes = OpenCVLearn.blurBilateralFilter(pixels, width, height);
        final Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        resultBitmap.setPixels(resultPixes, 0, width, 0, 0, width, height);

        MainThread.run(() -> ivImage2.setImageBitmap(resultBitmap));
    }
}
