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
#include <openssl/md5.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>


#ifdef __cplusplus
extern "C" {
#include <lua-5.4.3/lua.h>
#include <lua-5.4.3/lualib.h>
#include <lua-5.4.3/lauxlib.h>
};
extern"C" {
#endif

#define  LOG_TAG  "native-lib"


// 结构体
struct MemoryStruct {
    char *memory;
    size_t size;
};


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    auto *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *) realloc(mem->memory, mem->size + real_size + 1);
    if(!ptr) {
       __android_log_print(ANDROID_LOG_INFO, "native-lib", "not enough memory realloc returned NULL");
       return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, real_size);
    mem->size += real_size;
    mem->memory[mem->size] = 0;

    return real_size;
}

jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_requestByGet(
        JNIEnv* env,
        jobject obj, jstring url) {
    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "CURL_VERSION = %s",curl_version());

    const char *URL = env->GetStringUTFChars(url, 0);

    CURL *curl;

    CURLcode res;

    struct MemoryStruct chunk{};

    /* will be grown as needed by the realloc above */
    chunk.memory = (char *) malloc(1);
    /* no data at this point */
    chunk.size = 0;
    // 默认初始
    curl_global_init(CURL_GLOBAL_DEFAULT);

    std::string s;

    // 简易句柄
    curl = curl_easy_init();

    if (curl){
        // 设置URL
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        // 关闭证书校验
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        // 关闭主机名校验
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // send all data to this function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        // 30 秒内接收完成
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,60);

        // 证书位置
        //curl_easy_setopt(curl,CURLOPT_CAINFO,"");

        // 连接超时
        curl_easy_setopt( curl, CURLOPT_CONNECTTIMEOUT, 60);

        // 请求
        res = curl_easy_perform(curl);

        // 没有请求成功
        if(res != CURLE_OK){
            // 输出日志
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "curl_easy_perform() failed %s", curl_easy_strerror(res));
            __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "curl_easy_perform() failed %d",res);
            // 清理资源
            curl_easy_cleanup(curl);
        // 请求成功
        }

        if (chunk.size >0 ){
            s = chunk.memory;
        }else{
            s = "";
        }
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%zu", chunk.size);
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%d", s.length());
        // 申请的内存 要释放
        free(chunk.memory);
        // 避免野指针
        chunk.memory = nullptr;
    } else{
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "init curl failed");
    }
    // 释放curl 指针
    curl_global_cleanup();
    // 返回数据
    //return env->NewStringUTF(body);
    return env->NewStringUTF(s.c_str());
}

JNIEXPORT jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_helloBoost(JNIEnv *env, jobject thiz) {
    std::string Str = "Hello from C++\n";

    //-------------------------------------
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

    Str += "Boost version: " + Ver_Maj + "." + Ver_Min + "." + Ver_Pat + "\n";

    Str += "built with NDK version: " + std::string(BOOST_BUILT_WITH_NDK_VERSION) + "\n";

#if defined(__ANDROID_API__)
    Str += "native Api level: " + std::to_string(__ANDROID_API__) + "\n " ;
#endif

    Str += "\n";
    Str += "Boost chrono says time is \n" + std::string(buffer) + "\n\n";
    //--------------------------------------------

    return env->NewStringUTF(Str.c_str());;
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


static int
l_SayHello(lua_State *L)
{
    const char *d = luaL_checkstring(L, 1);//获取参数，字符串类型
    int len = strlen(d);
    char str[100] = "hello ";
    strcat(str, d);
    lua_pushstring(L, str);  // 返回给lua的值压栈
    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", str);
    return 1;
}

JNIEXPORT jstring JNICALL
Java_net_tusdasa_curl_RequestUtils_helloLua(JNIEnv *env, jobject thiz) {

    // 创建lua状态机
    lua_State *L = luaL_newstate();
    // 打开Lua状态机中所有Lua标准库
    luaL_openlibs(L);
    //注册C函数到lua
    lua_register(L, "SayHello", l_SayHello);
    //lua中调用c函数
    const char* testLuaFunction = "print(SayHello('lijia'))";
    // 执行Lua命令。
    if(luaL_dostring(L, testLuaFunction)){
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to invoke.");
    }else{
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", testLuaFunction);
    }
    // 清除Lua
    lua_close(L);

    return env->NewStringUTF("Hello");;
}

#ifdef __cplusplus
}
#endif