package com.tianshaokai.opencv;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

public class BlurActivity extends AppCompatActivity {

    private static final String TAG = "BlurActivity";
    private ImageView ivImage1, ivImage2;
    private TextView tvChange;
    private Bitmap bitmap;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_layout);

        ivImage1 = findViewById(R.id.ivImage1);
        ivImage2 = findViewById(R.id.ivImage2);
        tvChange = findViewById(R.id.tvChange);
        tvChange.setText("模糊效果");

        ThreadManagerUtils.getSingleThread().execute(new Runnable() {
            @Override
            public void run() {
                final long current = System.currentTimeMillis();
                bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.image1);

                MainThread.run(new Runnable() {
                    @Override
                    public void run() {
                        ivImage1.setImageBitmap(bitmap);
                    }
                });

                int width = bitmap.getWidth();
                int height = bitmap.getHeight();

                int[] pixels = new int[width * height];
                bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

                int[] resultPixes = OpenCVLearn.blur(pixels, width, height);
                final Bitmap result = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
                result.setPixels(resultPixes, 0, width, 0, 0, width, height);
                MainThread.run(new Runnable() {
                    @Override
                    public void run() {
                        long performance = System.currentTimeMillis() - current;
                        Log.d(TAG, "NDK耗时"+ String.valueOf(performance) + " 毫秒");
                        ivImage2.setImageBitmap(result);
                    }
                });
            }
        });
    }
}