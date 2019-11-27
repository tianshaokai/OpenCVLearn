package com.tianshaokai.opencv;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    private String[] permission = new String[]{Manifest.permission.CAMERA,
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE};

    private Button btnGray, btnBlur, btnBlur2, btnFace;
    private Context mContext;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mContext = this;
        btnGray = findViewById(R.id.btnGray);
        btnBlur = findViewById(R.id.btnBlur);
        btnBlur2 = findViewById(R.id.btnBlur2);
        btnFace = findViewById(R.id.btnFace);


        btnGray.setOnClickListener(onClickListener);
        btnBlur.setOnClickListener(onClickListener);
        btnBlur2.setOnClickListener(onClickListener);
        btnFace.setOnClickListener(onClickListener);
        // 版本判断。当手机系统大于 23 时，才有必要去判断权限是否获取
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // 检查该权限是否已经获取
            int i = ContextCompat.checkSelfPermission(this, permission[0]);
            // 权限是否已经 授权 GRANTED---授权  DINIED---拒绝
            if (i != PackageManager.PERMISSION_GRANTED) {
                // 如果没有授予该权限，就去提示用户请求
                ActivityCompat.requestPermissions(this, permission, 100);
            }
        }
    }

    private View.OnClickListener onClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.btnGray: {
                    Intent intent = new Intent(mContext, GrayActivity.class);
                    startActivity(intent);
                    break;
                }
                case R.id.btnBlur: {
                    Intent intent = new Intent(mContext, BlurActivity.class);
                    startActivity(intent);
                    break;
                }
                case R.id.btnBlur2: {
                    Intent intent = new Intent(mContext, BlurActivity2.class);
                    startActivity(intent);
                    break;
                }
                case R.id.btnFace: {
                    Intent intent = new Intent(mContext, FaceDetectorActivity.class);
                    startActivity(intent);
                    break;
                }
            }
        }
    };
}
