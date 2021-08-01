    package net.tusdasa.comic.adapter;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.bumptech.glide.Glide;

import net.tusdasa.comic.R;
import net.tusdasa.comic.model.Comic;
import net.tusdasa.comic.utils.CommonsUtils;

import org.jetbrains.annotations.NotNull;

import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Collections;
import java.util.Date;
import java.util.List;

public class ComicListDataAdapter extends RecyclerView.Adapter<ComicListDataAdapter.ComicListViewHolder> {

    private static String TAG = "ComicListDataAdapter";

    private Context context;

    private List<Comic> comicList;

    private OnItemClickListener onItemClickListener;

    private final Date toDay = new Date();

    public class ComicListViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {

        private ImageView comicCover;

        private TextView comicName;

        private TextView lastUpdate;

        private TextView comicHeat;

        private Comic comic;

        public ComicListViewHolder(@NonNull @NotNull View itemView) {
            super(itemView);
            comicCover = itemView.findViewById(R.id.comicCover);
            comicName = itemView.findViewById(R.id.comicName);
            lastUpdate = itemView.findViewById(R.id.lastUpdate);
            comicHeat = itemView.findViewById(R.id.comicHeat);
            itemView.setOnClickListener(this);
        }

        @Override
        public void onClick(View v) {
            onItemClickListener.onItemClick(v,comic);
        }
    }

    public ComicListDataAdapter(Context context) {
        this.context = context;
    }

    public void setDate(List<Comic> comicList){
        if (this.comicList == null){
            this.comicList = comicList;
        }else {
            this.comicList.addAll(comicList);
        }
        //notifyItemInserted(comicList.size());
        notifyDataSetChanged();

    }

    public void setOnItemClickListener(OnItemClickListener onItemClickListener){
        this.onItemClickListener = onItemClickListener;
    }

    @NonNull
    @NotNull
    @Override
    public ComicListViewHolder onCreateViewHolder(@NonNull @NotNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context)
                .inflate(
                        R.layout.comic_list_item,
                        parent,
                        false
                );
        ComicListViewHolder comicListViewHolder = new ComicListViewHolder(view);

        return comicListViewHolder; //new ComicListViewHolder(View.inflate(context, R.layout.comic_general_layout, null));
    }

    @Override
    public void onBindViewHolder(@NonNull @NotNull ComicListViewHolder holder, int position) {
        Comic comic = comicList.get(position);
        Log.i(TAG,"position:"+position +" comic: "+ comic.toString());
        holder.comic = comic;
        Glide.with(context).load(comic.getComic_cover())
                .placeholder(R.drawable.ic_loading).into(holder.comicCover);

        holder.lastUpdate.setText(
                "更新于 "+
                CommonsUtils.differentDaysByMillisecond(comic.getUpdated_at(), toDay)
                +"天前"
        );

        holder.comicHeat.setText("热度: "+comic.getPoint().toString());

        holder.comicName.setText(comic.getComic_name());


    }

    @Override
    public int getItemCount() {
        return comicList!=null?comicList.size():0;
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public int getItemViewType(int position) {
        return position;
    }

    public interface OnItemClickListener{
        void onItemClick(View view, Comic comic);
    }
}
