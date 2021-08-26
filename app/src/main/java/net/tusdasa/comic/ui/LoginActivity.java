package net.tusdasa.comic.ui;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;

import net.tusdasa.comic.R;
import net.tusdasa.curl.RequestUtils;

public class LoginActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText username;

    private EditText password;

    private ProgressBar progressBar;

    private Button login;

    private RequestUtils requestUtils = RequestUtils.getInstance();

    private final Handler mHandler = new Handler(Looper.myLooper(), msg ->{
        return false;
    });

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        //
        this.username = findViewById(R.id.username);
        //
        this.password = findViewById(R.id.password);
        //
        this.progressBar = findViewById(R.id.loading);

        //
        this.login = findViewById(R.id.login);

        //RequestUtils requestUtils = RequestUtils.getInstance();

        //requestUtils.helloBoost();

        //Log.i(TAG, requestUtils.helloBoost());

        login.setOnClickListener(this);
    }


    @Override
    public void onClick(View view) {
        if (view.getId() == R.id.login){
            String TAG = "LoginActivity";
            Log.i(TAG,"LOGIN");

            String username = this.username.getText().toString();
            String password = this.password.getText().toString();

            if (!username.isEmpty() && !password.isEmpty()){
                Intent intent = new Intent(LoginActivity.this, ComicListActivity.class);
               // Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                startActivity(intent);
            }

            // 开启新线程
            new Thread(()->{
            }).start();

        }
    }
}