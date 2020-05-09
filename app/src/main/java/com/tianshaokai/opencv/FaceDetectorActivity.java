package com.tianshaokai.opencv;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.annotation.RawRes;
import androidx.appcompat.app.AppCompatActivity;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * Author : tianshaokai
 * Date   : 2019/11/27 22:08
 * Desc   :
 * Since  :
 */
public class FaceDetectorActivity extends AppCompatActivity {
    private static final String TAG = "FaceDetectorActivity";
    private ImageView ivImage1, ivImage2;
    private TextView tvChange;

    private Bitmap bitmap;

    private File mCascadeFile;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_layout);
        ivImage1 = findViewById(R.id.ivImage1);
        ivImage2 = findViewById(R.id.ivImage2);
        tvChange = findViewById(R.id.tvChange);
        tvChange.setText("识别");


        ThreadManagerUtils.getSingleThread().execute(() -> {
            final long current = System.currentTimeMillis();
            bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.image1);

            //人脸检测
            copyCascadeFile(R.raw.lbpcascade_frontalface, "lbpcascade_frontalface.xml");
//                copyCascadeFile(R.raw.lbpcascade_frontalcatface, "lbpcascade_frontalcatface.xml");
//                copyCascadeFile(R.raw.lbpcascade_frontalface_improved, "lbpcascade_frontalface_improved.xml");
//                copyCascadeFile(R.raw.lbpcascade_profileface, "lbpcascade_profileface.xml");
//                copyCascadeFile(R.raw.lbpcascade_silverware, "lbpcascade_silverware.xml");

            MainThread.run(() -> ivImage1.setImageBitmap(bitmap));

            final int count = OpenCVLearn.faceDetector(bitmap, Bitmap.Config.ARGB_8888, mCascadeFile.getPath());

            MainThread.run(() -> Toast.makeText(FaceDetectorActivity.this, "检测到 " + count + " 个人脸", Toast.LENGTH_SHORT).show());


            final Bitmap bitmapResult = OpenCVLearn.faceDetectorResize(bitmap, Bitmap.Config.ARGB_8888,
                    mCascadeFile.getPath(),413,626);

            MainThread.run(() -> ivImage2.setImageBitmap(bitmapResult));
        });

    }

    private void copyCascadeFile(@RawRes int resId, String resName) {
        InputStream inputStream = getResources().openRawResource(resId);
        File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
        mCascadeFile = new File(cascadeDir, resName);
        if(mCascadeFile.exists()) return;

        try {
            FileOutputStream fileOutputStream = new FileOutputStream(mCascadeFile);
            byte[] buffer = new byte[4096];
            int len = 0;
            while ((len = inputStream.read(buffer)) != -1) {
                fileOutputStream.write(buffer, 0, len);
            }
            inputStream.close();
            fileOutputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
