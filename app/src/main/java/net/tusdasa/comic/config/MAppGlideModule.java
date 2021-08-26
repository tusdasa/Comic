package net.tusdasa.comic.config;

import android.content.Context;

import androidx.annotation.NonNull;

import com.bumptech.glide.Glide;
import com.bumptech.glide.GlideBuilder;
import com.bumptech.glide.Registry;
import com.bumptech.glide.annotation.GlideModule;
import com.bumptech.glide.integration.okhttp3.OkHttpUrlLoader;
import com.bumptech.glide.load.engine.cache.DiskLruCacheFactory;
import com.bumptech.glide.load.model.GlideUrl;
import com.bumptech.glide.module.AppGlideModule;

import java.io.InputStream;

@GlideModule
public class MAppGlideModule extends AppGlideModule {

    @Override
    public void applyOptions(@NonNull Context context, @NonNull GlideBuilder builder) {
        super.applyOptions(context, builder);
        builder.setDiskCache(new DiskLruCacheFactory(context.getExternalCacheDir().getAbsolutePath(),240*1024*1024));
    }
    @Override
    public boolean isManifestParsingEnabled() {
        return false;
    }

    @Override
    public void registerComponents(@NonNull Context context, @NonNull Glide glide, @NonNull Registry registry) {
        //super.registerComponents(context, glide, registry);
        registry.replace(GlideUrl.class, InputStream.class, new OkHttpUrlLoader.Factory());
    }
}
