package net.tusdasa.curl;

import java.util.Calendar;

public class RequestUtils {
    static{
        System.loadLibrary("native-lib");
    }

    private static class RequestUtilsHolder {
        private static final RequestUtils requestUtils = new RequestUtils();
    }

    public static RequestUtils getInstance(){
        return RequestUtils.RequestUtilsHolder.requestUtils;
    }

    protected RequestUtils() {
    }

    public native String requestByGet(String url);

    public native String helloBoost();

    public native String getCurrentTime();

    // public native Calendar getCalendar();

    public native String helloLua();

    public native String signature(String str);
}
