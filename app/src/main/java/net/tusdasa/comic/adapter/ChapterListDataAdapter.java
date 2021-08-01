package net.tusdasa.comic.adapter;

import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import org.jetbrains.annotations.NotNull;

public class ChapterListDataAdapter extends RecyclerView.Adapter<ChapterListDataAdapter.ChapterViewHolder> {


    public class  ChapterViewHolder extends RecyclerView.ViewHolder{
        public ChapterViewHolder(@NonNull @NotNull View itemView) {
            super(itemView);
        }
    }

    @NonNull
    @NotNull
    @Override
    public ChapterViewHolder onCreateViewHolder(@NonNull @NotNull ViewGroup parent, int viewType) {
        return null;
    }

    @Override
    public void onBindViewHolder(@NonNull @NotNull ChapterViewHolder holder, int position) {

    }


    @Override
    public int getItemCount() {
        return 0;
    }
}
