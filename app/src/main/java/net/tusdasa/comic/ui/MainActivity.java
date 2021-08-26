package net.tusdasa.comic.ui;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;

import net.tusdasa.comic.R;
import net.tusdasa.comic.ui.fragment.CategoryFragment;
import net.tusdasa.comic.ui.fragment.HomeFragment;
import net.tusdasa.comic.ui.fragment.ProfileFragment;
import net.tusdasa.comic.ui.fragment.SettingFragment;
import net.tusdasa.curl.RequestUtils;

public class MainActivity extends FragmentActivity implements View.OnClickListener {

    private static final String TAG = "MainActivity";


    private ImageButton mHome;
    private ImageButton mComic;
    private ImageButton mProfile;
    private ImageButton mSetting;


    private RequestUtils requestUtils = RequestUtils.getInstance();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mHome = findViewById(R.id.button_home);

        mComic = findViewById(R.id.button_comic);

        mProfile = findViewById(R.id.button_profile);

        mSetting = findViewById(R.id.button_setting);

        //

        mHome.setOnClickListener(this::onClick);
        mComic.setOnClickListener(this::onClick);
        mProfile.setOnClickListener(this::onClick);
        mSetting.setOnClickListener(this::onClick);



        Log.i(TAG, requestUtils.signature("1629022582v19a09bff383347f49dda80fbe612d865f313cf72ewebandroid1.0.19baf861a-0892-46bf-92bf-4bb2eacab090"));
        Log.i(TAG,requestUtils.helloLua());


    }

    @Override
    public void onClick(View v) {
        if (v.getId() == R.id.button_home){
            replaceFragment(new HomeFragment());
        }

        if (v.getId() == R.id.button_comic){
            replaceFragment(new CategoryFragment());
        }

        if (v.getId() == R.id.button_profile){
            replaceFragment(new ProfileFragment());
        }

        if (v.getId() == R.id.button_setting){
            replaceFragment(new SettingFragment());
        }
    }


    private void replaceFragment(Fragment fragment){
        FragmentManager fragmentManager = this.getSupportFragmentManager();

        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();

        fragmentTransaction.replace(R.id.f1, fragment);

        fragmentTransaction.commit();
    }
}