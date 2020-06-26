package com.tianshaokai.opencv.ui;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.tianshaokai.opencv.MainThread;
import com.tianshaokai.opencv.OpenCVLearn;
import com.tianshaokai.opencv.R;
import com.tianshaokai.opencv.ThreadManagerUtils;

import java.io.File;

public class IDCardActivity extends AppCompatActivity {

    private static final String TAG = "IDCardActivity";
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
        tvChange.setText("获取身份证号");

        ThreadManagerUtils.getSingleThread().execute(() -> {
            String path = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DCIM).getAbsolutePath();

            bitmap = BitmapFactory.decodeFile(path + File.separator + "WechatIMG53.jpeg");

            MainThread.run(() -> ivImage1.setImageBitmap(bitmap));

            Bitmap idCardBitmap = OpenCVLearn.getIdCardNumber(bitmap, Bitmap.Config.ARGB_8888);
            MainThread.run(() -> {
                ivImage2.setImageBitmap(idCardBitmap);
                bitmap.recycle();
            });
        });
    }
}
