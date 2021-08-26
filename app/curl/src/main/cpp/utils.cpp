//
// Created by Administrator on 8/19/2021.
//

#include "utils.h"
#include <openssl/sha.h>
#include <sstream>
#include <boost/lexical_cast.hpp>

#define LOG_UTILS "utils"

#define SERVER_API_VERSION "v1.0"
#define APP_Platform "Android"
#define APP_BuildVersion "dev_0.1"

const char * apiVersion = SERVER_API_VERSION;
const char * appBuildVersion = APP_BuildVersion;
const char * appPlatform = APP_Platform;



// __VA_ARGS__ https://blog.csdn.net/q2519008/article/details/80934815
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_UTILS, __VA_ARGS__)


std::string
sha(const std::string& source){
    char buf[3];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, source.c_str(), source.size());
    SHA256_Final(hash, &sha256);
    std::string destination;
    for(unsigned char i : hash)
    {
        sprintf(buf,"%02x",i);
        destination.append(buf);
    }
    return destination;
}

static int
l_SayHello(lua_State *L)
{
    //获取参数，字符串类型
    const char *d = luaL_checkstring(L, 1);
    // int len = stolen(d);
    char str[100] = "Hello ";
    strcat(str, d);
    // 返回给lua的值压栈
    lua_pushstring(L, str);
    //_android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "%d", lua_gettop(L));
    LOGI("%d", lua_gettop(L));
    return 1;
}

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    auto *mem = (struct MemoryStruct *)userp;

    char *ptr = (char *) realloc(mem->memory, mem->size + real_size + 1);
    if(!ptr) {
        LOGI("not enough memory realloc returned NULL");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, real_size);
    mem->size += real_size;
    mem->memory[mem->size] = 0;

    return real_size;
}



std::string
runLua(const std::string& source){
    // 创建lua状态机
    lua_State *L = luaL_newstate();
    // 打开Lua状态机中所有Lua标准库
    luaL_openlibs(L);

    //注册C函数到lua
    lua_register(L, "SayHello", l_SayHello);
    //lua中调用c函数
    const char* testLuaFunction = "SayHello('Lua')";

    lua_getglobal(L, "SayHello");
    lua_pushstring(L,source.c_str());
    // 执行Lua命令。
    //luaL_dostring(L, testLuaFunction)
    // 1 个参数 1 个返回值
    if(lua_pcall(L,1,1,0)){
        //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "Failed to invoke.");
        LOGI("Failed to invoke.");
    }else{
        //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "%s", testLuaFunction);
        LOGI("%s", testLuaFunction);
    }
    // 清除Lua
    //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "lua_gettop %d", lua_gettop(L));
    LOGI("lua_gettop %d", lua_gettop(L));
    //__android_log_print(ANDROID_LOG_ERROR, "utils", "is %f", lua_tonumber(L,-1));

    if (lua_isstring(L,1)){
        //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "is %s", lua_tostring(L,1));
        LOGI("is %s", lua_tostring(L,1));
    }

    // 取出
    std::string ss = lua_tostring(L,1);
    // 移除
    lua_remove(L,1);
    // 关闭Lua
    lua_close(L);

    return ss;

}

std::string CurlRequest(const std::string& url,
                        const std::string& apiKey,
                        const std::string& uuid,
                        const std::string& appChannel){

    LOGI("CURL_VERSION = %s",curl_version());

    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk{};
    struct curl_slist *list = nullptr;

    /* will be grown as needed by the realloc above */
    chunk.memory = (char *) malloc(1);
    /* no data at this point */
    chunk.size = 0;
    // 默认初始
    curl_global_init(CURL_GLOBAL_DEFAULT);

    std::string body;

    // 简易句柄
    curl = curl_easy_init();

    if (curl){
        /*
        struct curl_blob stblob{};
        stblob.data = (void *)clinet;
        stblob.len = strlen(clinet);
        stblob.flags = CURL_BLOB_COPY;
        curl_easy_setopt(curl, CURLOPT_SSLCERT_BLOB, &stblob);
         */

        // 设置URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // 关闭证书校验
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        // 关闭主机名校验
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // send all data to this function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        // 60 秒内接收完成
        curl_easy_setopt(curl,CURLOPT_TIMEOUT,60);

        // 时间戳

        std::stringstream ss2 ;
        time_t timestamp = time(nullptr);
        //const char * apiKey="9a09bff383347f49dda80fbe612d865f313cf72e";
        //const char * appChannel="web";
        //const char * uuid="9baf861a-0892-46bf-92bf-4bb2eacab090";
        //timestamp..apiVersion..apiKey..appChannel..appPlatform..appBuildVersion..uuid
        ss2 << boost::lexical_cast<std::string>(timestamp) << apiVersion << apiKey << appChannel << appPlatform << appBuildVersion << uuid;
        LOGI("%ld",timestamp);
        // 签名处理
        std::string x_signature ="x-signature:";
        x_signature.append(sha(ss2.str()));

        std::string x_api_key = "x-api-key:";
        x_api_key.append(apiKey);

        std::string x_timestamp = "x-timestamp:";
        x_timestamp.append(boost::lexical_cast<std::string>(timestamp));

        std::string x_api_version = "x-api-version:";
        x_api_version.append(SERVER_API_VERSION);

        std::string x_app_channel = "x-app-channel:";
        x_app_channel.append(appChannel);

        std::string x_app_platform = "x-app-platform:";
        x_app_platform.append(APP_Platform);

        std::string x_build_version = "x-build-version:";
        x_build_version.append(APP_BuildVersion);

        std::string x_uuid = "x-uuid:";
        x_uuid.append(uuid);

        //free(&src);

        // 添加签名
        list = curl_slist_append(list, x_signature.c_str());
        list = curl_slist_append(list, x_api_key.c_str());
        list = curl_slist_append(list, x_timestamp.c_str());
        list = curl_slist_append(list, x_api_version.c_str());
        list = curl_slist_append(list, x_app_channel.c_str());
        list = curl_slist_append(list, x_build_version.c_str());
        list = curl_slist_append(list, x_uuid.c_str());
        list = curl_slist_append(list, x_app_platform.c_str());

/*
        list = curl_slist_append(list, "x-signature:f01a7e5979cb7fd20527487fcfbb48df261a2ef7e21dd431cd181667a88c612e");
        list = curl_slist_append(list, "x-timestamp:1629022582");
        list = curl_slist_append(list, "x-api-version:v1");
        list = curl_slist_append(list, "x-app-channel:web");
        list = curl_slist_append(list, "x-app-platform:android");
        list = curl_slist_append(list, "x-api-key:9a09bff383347f49dda80fbe612d865f313cf72e");
        list = curl_slist_append(list, "x-build-version:1.0.1");
        list = curl_slist_append(list, "x-uuid:9baf861a-0892-46bf-92bf-4bb2eacab090");
*/
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER, list);
        // 证书位置
        //curl_easy_setopt(curl,CURLOPT_CAINFO,"");

        // 连接超时
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 60);

        // 请求
        res = curl_easy_perform(curl);

        // 没有请求成功
        if(res != CURLE_OK){
            // 输出日志
            //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "curl_easy_perform() failed %s", curl_easy_strerror(res));
            //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "curl_easy_perform() failed %d",res);
            LOGI("curl_easy_perform() failed %s", curl_easy_strerror(res));
            LOGI("curl_easy_perform() failed %d",res);

            // 清理资源
            curl_easy_cleanup(curl);
            // 请求成功
        }

        if (chunk.size >0 ){
            body = chunk.memory;
        }else{
            body = "";
        }
        //LOGI("%s", body.c_str());
        //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "%zu", chunk.size);
        LOGI("%zu", chunk.size);
        //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "%d", s.length());
        LOGI("%d", body.length());
        // 申请的内存 要释放
        free(chunk.memory);
        // 避免野指针
        chunk.memory = nullptr;
    } else{
        //__android_log_print(ANDROID_LOG_ERROR, LOG_UTILS, "init curl failed");
        LOGI("init curl failed");
    }
    // 释放curl 指针
    curl_slist_free_all(list);
    curl_global_cleanup();

    return body;
}