package net.tusdasa.comic.ui;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;

import net.tusdasa.comic.R;
import net.tusdasa.comic.model.Comic;
import net.tusdasa.comic.utils.CommonsUtils;
import net.tusdasa.curl.RequestUtils;

import java.util.Date;

public class ComicDetailActivity extends AppCompatActivity {

    private static final String TAG = "ComicDetailActivity";

    // 封面
    private ImageView detailsCover;
    // 名称
    private TextView detailsName;
    // 最后更新
    private TextView detailsLastUpdate;
    // 热度
    private TextView detailsHeat;

    // 介绍
    private TextView introduction;

    private RecyclerView chapterList;

    private final RequestUtils requestUtils = RequestUtils.getInstance();

    private final Handler mHandler = new Handler(Looper.myLooper(), msg -> {
        return false;
    });

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_comic_chapter);

        detailsCover = findViewById(R.id.detailsCover);
        detailsName = findViewById(R.id.detailsName);
        detailsLastUpdate = findViewById(R.id.detailsLastUpdate);
        detailsHeat = findViewById(R.id.detailsHeat);
        introduction = findViewById(R.id.introduction);
        chapterList = findViewById(R.id.chapterList);

        Intent intent = getIntent();

        // 接收当前漫画
        Comic comic = (Comic) intent.getBundleExtra("comic").getSerializable("comic");

        Log.i(TAG,comic.toString());

        Glide.with(this).load(comic.getComic_cover()).placeholder(R.drawable.ic_loading).into(detailsCover);
        detailsName.setText(comic.getComic_name());
        detailsLastUpdate.setText("更新于 "+
                CommonsUtils.differentDaysByMillisecond(comic.getUpdated_at(), new Date())
                +"天前");

        detailsHeat.setText("热度: "+comic.getPoint().toString());

        introduction.setText(comic.getIntroduction());

        //loadDate(comic.getComic_id());

    }

    private void loadDate(Long comicId){

        // 异步
        new Thread(()->{

            String resp = requestUtils.
                    requestByGet("https://www.tusdasa.net:8080/api/comic/findchapter?comicid="+ comicId);

            Message message = Message.obtain();
            Bundle bundle = new Bundle();

            if (resp!=null && !resp.isEmpty()){
                bundle.putString("res", resp);
                message.setData(bundle);
                message.what = 0;
            }else {
                message.what = 1;
            }
            mHandler.sendMessage(message);

        }).start();
    }
}