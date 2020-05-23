package com.tianshaokai.opencv;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

public class GrayActivity extends AppCompatActivity {

    private static final String TAG = "GrayActivity";
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
        tvChange.setText("变灰后");

        ThreadManagerUtils.getSingleThread().execute(() -> {
            bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.image1);

            MainThread.run(() -> ivImage1.setImageBitmap(bitmap));

            int width = bitmap.getWidth();
            int height = bitmap.getHeight();

            int[] pixels = new int[width * height];
            bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

            int[] resultPixes = OpenCVLearn.gray(pixels, width, height);
            final Bitmap result = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
            result.setPixels(resultPixes, 0, width, 0, 0, width, height);

            MainThread.run(() -> ivImage2.setImageBitmap(result));
        });
    }
}
