package com.tianshaokai.opencv.ui;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.tianshaokai.opencv.MainThread;
import com.tianshaokai.opencv.R;
import com.tianshaokai.opencv.ThreadManagerUtils;

public class GrayActivity2 extends AppCompatActivity {

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


        });
    }
}
