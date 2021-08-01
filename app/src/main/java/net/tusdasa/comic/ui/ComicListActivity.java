package net.tusdasa.comic.ui;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import net.tusdasa.comic.R;
import net.tusdasa.comic.adapter.ComicListDataAdapter;
import net.tusdasa.comic.model.Comic;
import net.tusdasa.curl.RequestUtils;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class ComicListActivity extends AppCompatActivity implements ComicListDataAdapter.OnItemClickListener{

    private static final String TAG = ComicListActivity.class.getSimpleName();

    private int page =0;

    private RecyclerView recyclerView;

    private  ProgressBar startProgressBar;

    private ProgressBar endProgressBar;

    private final RequestUtils requestUtils = RequestUtils.getInstance();

    private final Gson gson = new GsonBuilder().setDateFormat("yyyy-MM-dd HH:mm:ss").create();

    private ComicListDataAdapter comicListDataAdapter;

    private boolean isSlidingToLast = false;

    // 事件回调通知
    private final Handler mHandler = new Handler(Looper.myLooper(), msg -> {
        if (msg.what == 0){
            Comic[] comicsArray = gson.fromJson(msg.getData().getString("res"), Comic[].class);
            List<Comic> comicList = new ArrayList<>(comicsArray.length); //Arrays.asList(comicsArray);
            comicList.addAll(Arrays.asList(comicsArray));
            //Collections.addAll(comicList,comicsArray);
            //comicList.addAll(Arrays.asList(comicsArray));
            Log.i(TAG,comicList.toString());
            comicListDataAdapter.setDate(comicList);
            recyclerView.setVisibility(View.VISIBLE);
            startProgressBar.setVisibility(View.GONE);
            endProgressBar.setVisibility(View.GONE);
            // 通知数据发送变化

            //comicListDataAdapter.notifyDataSetChanged();
        }

        if (msg.what == 1){
            Toast.makeText(ComicListActivity.this,"没有更多了",Toast.LENGTH_LONG).show();
        }

        return false;
    });


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_comic_list);

        // 默认不可见
        recyclerView = findViewById(R.id.comicList);

        startProgressBar = findViewById(R.id.startLoading);

        endProgressBar = findViewById(R.id.endLoading);

        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        comicListDataAdapter = new ComicListDataAdapter(ComicListActivity.this);

        //comicListDataAdapter.setHasStableIds(true);
        recyclerView.setAdapter(comicListDataAdapter);

        comicListDataAdapter.setOnItemClickListener(this::onItemClick);

        recyclerView.addOnScrollListener(new RecyclerView.OnScrollListener() {
            @Override
            public void onScrollStateChanged(@NonNull @NotNull RecyclerView recyclerView, int newState) {
                super.onScrollStateChanged(recyclerView, newState);
                //Log.i(TAG,"onScrollStateChanged: "+newState);
                RecyclerView.LayoutManager layoutManager = recyclerView.getLayoutManager();
                LinearLayoutManager linearLayoutManager = (LinearLayoutManager) layoutManager;
                if (newState == RecyclerView.SCROLL_STATE_IDLE){
                    assert linearLayoutManager != null;
                    if (linearLayoutManager.findLastVisibleItemPosition() +1 == linearLayoutManager.getItemCount() && isSlidingToLast){
                        Log.i(TAG,"滑到了最后一个");
                        page+=1;
                        endProgressBar.setVisibility(View.VISIBLE);
                        loadData(page);
                    }

                }
            }

            @Override
            public void onScrolled(@NonNull @NotNull RecyclerView recyclerView, int dx, int dy) {
                super.onScrolled(recyclerView, dx, dy);
                //Log.i(TAG,"onScrolled: "+dx+"  :"+dy);

                if (dy > 0){
                    isSlidingToLast = true;
                }else {
                    isSlidingToLast = false;
                }
            }
        });

        this.loadData(page);
    }

    @Override
    public void onItemClick(View view, Comic comic) {
        Log.i(TAG,"onItemClick ID:"+comic.getComic_id());

        Intent intent = new Intent(this, ComicDetailActivity.class);
        Bundle bundle = new Bundle();
        bundle.putSerializable("comic",comic);
        intent.putExtra("comic", bundle);
        startActivity(intent);
    }

    private void loadData(int page){
        // 异步
        new Thread(()->{

            String resp = requestUtils.requestByGet("https://www.tusdasa.net:8080/api/comic/findall?page="+String.valueOf(page));

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