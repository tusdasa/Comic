package net.tusdasa.comic;

import android.app.Application;

import net.tusdasa.comic.utils.ObjectBoxUtils;

public class ComicApp extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        // 初始化
        ObjectBoxUtils.init(this);
    }
}
