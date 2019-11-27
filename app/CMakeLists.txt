# 设置Cmake最小版本
cmake_minimum_required(VERSION 3.4.1)

#输出详细信息
set(CMAKE_VERBOSE_MAKEFILE on)

# 编译library # SHARED模式会编译so文件，STATIC模式不会编译
add_library(opencv_learn SHARED
        src/main/cpp/OpenCVLearn.cpp)

#设置库目录，以下会用到
set(LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

# 包含头文件目录
include_directories(src/main/cpp/include)

#添加 opencv 的动态库
add_library(opencv_java4 SHARED IMPORTED )

#指定库路径
set_target_properties(opencv_java4 PROPERTIES IMPORTED_LOCATION ${LIBRARY_DIRS}/${ANDROID_ABI}/libopencv_java4.so)

find_library(log-lib log)

target_link_libraries(
        opencv_learn

        # Links the target library to the log library
        # included in the NDK.
        opencv_java4
        jnigraphics
        ${log-lib})