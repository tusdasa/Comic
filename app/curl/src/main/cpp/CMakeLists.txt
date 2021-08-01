# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.

project("Comic")


add_library(
        native-lib
        SHARED
        native-lib.cpp)

add_library(lua SHARED
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lapi.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lcode.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lctype.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/ldebug.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/ldo.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/ldump.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lfunc.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lgc.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/llex.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lmem.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lobject.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lopcodes.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lparser.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lstate.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lstring.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/ltable.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/ltm.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lundump.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lvm.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lzio.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lauxlib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lbaselib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lcorolib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/ldblib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/liolib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lmathlib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/loadlib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/loslib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lstrlib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/ltablib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/lutf8lib.c
        ${CMAKE_SOURCE_DIR}/lua-5.4.3/src/linit.c)

#
include_directories(include)

# curl
add_library(curl SHARED IMPORTED)

set_target_properties(curl
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libcurl.so)


# ssl
add_library(ssl STATIC IMPORTED)

set_target_properties(ssl
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libssl.a)

# crypto
add_library(crypto STATIC IMPORTED)

set_target_properties(crypto
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libcrypto.a)
# libz
add_library(z SHARED IMPORTED)

set_target_properties(z
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libz.so
        )

# boost_system
add_library (boost_system SHARED IMPORTED)

set_target_properties(boost_system
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libboost_system.so
        )

# libboost_chrono
add_library(boost_chrono SHARED IMPORTED)

set_target_properties(boost_chrono
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libboost_chrono.so
        )

# 增加 libc++_shared.so
# sysroot/usr/lib/aarch64-linux-android/libc++_shared.so
# sysroot/usr/lib/arm-linux-androideabi/libc++_shared.so
# sysroot/usr/lib/i686-linux-android/libc++_shared.so
# sysroot/usr/lib/x86_64-linux-android/libc++_shared.so
add_library(c++_shared SHARED IMPORTED)

set_target_properties(c++_shared
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libc++_shared.so
        )

#add_library(luajit SHARED IMPORTED)

#set_target_properties(luajit
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../libs/${ANDROID_ABI}/libluajit.so
#        )

# log
find_library(
        log-lib
        log )

target_link_libraries(native-lib
        curl
        ssl
        crypto
        ${log-lib})

target_link_libraries(native-lib
        boost_system
        boost_chrono
        lua
        c++_shared
        z
)




