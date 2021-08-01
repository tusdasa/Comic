package net.tusdasa.comic.utils;

import android.content.Context;

import net.tusdasa.comic.model.MyObjectBox;

import io.objectbox.BoxStore;

public class ObjectBoxUtils {

    private static BoxStore boxStore;

    public static void init(Context context) {
        boxStore = MyObjectBox.builder()
                .androidContext(context.getApplicationContext())
                .build();
    }

    public static BoxStore get() { return boxStore; }
}
