package net.tusdasa.comic.utils;

import java.util.Date;

public class CommonsUtils {

    public static String differentDaysByMillisecond(Date date1, Date date2)
    {
        int days = (int) ((date2.getTime() - date1.getTime()) / (1000*3600*24));
        return String.valueOf(days);
    }
}
