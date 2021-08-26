#include <jni.h>
#include <string>
#include <malloc.h>
#include <android/log.h>
#include <curl/curl.h>
#include <boost/chrono.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/version_ndk.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <ctime>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "utils.h"

#ifdef __cplusplus
extern"C" {
#endif

jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_requestByGet(
        JNIEnv* env,
        jobject obj, jstring url) {
    // 获取URL
    const char *URL = env->GetStringUTFChars(url, nullptr);

    // 返回数据
    //return env->NewStringUTF(body);
    return env->NewStringUTF(
            CurlRequest(
                    URL,
                    "9a09bff383347f49dda80fbe612d865f313cf72e",
                    "9baf861a-0892-46bf-92bf-4bb2eacab090",
                    "web"
                    ).c_str()
                    );
}

JNIEXPORT jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_helloBoost(JNIEnv *env, jobject thiz) {

    boost::property_tree::ptree ptre;

    std::stringstream  ss1;

    ptre.put("title","Hello from C++");

    boost::chrono::system_clock::time_point p  = boost::chrono::system_clock::now();
    std::time_t t = boost::chrono::system_clock::to_time_t(p);

    char buffer[26];
    ctime_r(&t, buffer);

    int ver = BOOST_VERSION;
    int ver_maj = ver/100000;
    int ver_min = ver / 100 %1000;
    int ver_pat = ver %100;

    std::string Ver_Maj = boost::lexical_cast<std::string>(ver_maj);
    std::string Ver_Min = boost::lexical_cast<std::string>(ver_min);
    std::string Ver_Pat = boost::lexical_cast<std::string>(ver_pat);

    ptre.put("Boost version", Ver_Maj + "." + Ver_Min + "." + Ver_Pat);

    ptre.put("built with NDK version", std::string(BOOST_BUILT_WITH_NDK_VERSION));

#if defined(__ANDROID_API__)
    ptre.put("Native Api level", std::to_string(__ANDROID_API__));
#endif
    ptre.put("Boost chrono says time is", std::string(buffer));

    boost::property_tree::write_json(ss1, ptre);

    // std::string jsonContent = ss1.str();

    return env->NewStringUTF(ss1.str().c_str());;
}

JNIEXPORT jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_getCurrentTime(JNIEnv *env, jobject thiz) {

    //using namespace ;
   // using namespace boost::gregorian;

    const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();

    // Get the time offset in current day
    const boost::posix_time::time_duration td = now.time_of_day();

    int hh = td.hours();
    int mm = td.minutes();
    int ss = td.seconds();

    tm local_tm = boost::posix_time::to_tm(now);


    //t1 = localtime(&current_time);
    //int ms = td.total_milliseconds() - ((hh * 3600 + mm * 60 + ss) * 1000);

   jclass calendar_class = env->FindClass("java/util/Calendar");
   jmethodID getInstance_id = env->GetStaticMethodID(calendar_class,"getInstance","()Ljava/util/Calendar;");
   jmethodID add_id = env->GetMethodID(calendar_class,"add", "(II)V");
    //jmethodID getInstance_id = env->GetStaticMethodID(calendar_class,"","");
    //jmethodID getInstance_id = env->GetStaticMethodID(calendar_class,"","");
    //jmethodID getInstance_id = env->GetStaticMethodID(calendar_class,"","");
    //jmethodID getInstance_id = env->GetStaticMethodID(calendar_class,"","");

   if (getInstance_id){
       jobject  callendar_obj = env->CallStaticObjectMethod(calendar_class, getInstance_id);
       env->CallVoidMethod(callendar_obj,add_id,1,local_tm.tm_year+1900);
       env->CallVoidMethod(callendar_obj,add_id,2,local_tm.tm_mon);
       env->CallVoidMethod(callendar_obj,add_id,5,local_tm.tm_mday);
       env->CallVoidMethod(callendar_obj,add_id,10,hh);
       env->CallVoidMethod(callendar_obj,add_id,12,mm);
       env->CallVoidMethod(callendar_obj,add_id,13,ss);
   }


    //return mktime() * 1000;

    std::stringstream stream;
    stream << hh << ":" << mm << ":" << ss;

    return env->NewStringUTF(stream.str().c_str());
}

/*
JNIEXPORT jobject JNICALL
Java_net_tusdasa_curl_RequestUtils_getCalendar(JNIEnv *env, jobject thiz) {

    jclass calendar_class = env->FindClass("java/util/Calendar");
    jmethodID getInstance_id = env->GetStaticMethodID(calendar_class,"getInstance","()Ljava/util/Calendar;");

    //if (getInstance_id){
    jobject  callendar_obj = env->CallStaticObjectMethod(calendar_class, getInstance_id);

    //__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s",local_tm.tm_zone);
    //}
    //env->DeleteLocalRef(calendar_class);
    return callendar_obj;
}
*/


JNIEXPORT jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_helloLua(JNIEnv *env, jobject thiz) {

    std::string sss = runLua("Lua");

    return env->NewStringUTF(sss.c_str());
}

JNIEXPORT jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_signature(JNIEnv *env, jobject thiz, jstring str) {

    std::string source = env->GetStringUTFChars(str,0);

    return env->NewStringUTF(sha(source).c_str());
}

#ifdef __cplusplus
}
#endif