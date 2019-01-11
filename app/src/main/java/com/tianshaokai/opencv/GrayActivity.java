package com.tianshaokai.opencv;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;

public class GrayActivity extends AppCompatActivity {

    private static final String TAG = "GrayActivity";
    private Button tvChange;
    private ImageView ivImage1, ivImage2;
    private Context mContext;
    private Bitmap bitmap;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_gray);
        mContext = this;
        tvChange = findViewById(R.id.tvChange);

        ivImage1 = findViewById(R.id.ivImage1);
        ivImage2 = findViewById(R.id.ivImage2);

        tvChange.setOnClickListener(onClickListener);

        bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.image1);

        ivImage1.setImageBitmap(bitmap);
    }

    private View.OnClickListener onClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.tvChange:{
                    if (bitmap == null) {
                        Toast.makeText(mContext, "请选择图片", Toast.LENGTH_SHORT).show();
                        return;
                    }

                    ThreadManagerUtils.getSingleThread().execute(new Runnable() {
                        @Override
                        public void run() {
                            final long current = System.currentTimeMillis();
                            int width = bitmap.getWidth();
                            int height = bitmap.getHeight();

                            int[] pixels = new int[width * height];
                            bitmap.getPixels(pixels, 0, width, 0, 0, width, height);

                            int[] resultPixes = OpenCVLearn.gray(pixels, width, height);
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
                    break;
                }
            }
        }
    };
}
