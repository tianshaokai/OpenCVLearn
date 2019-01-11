# 设置Cmake最小版本
cmake_minimum_required(VERSION 3.4.1)


#输出详细信息
set(CMAKE_VERBOSE_MAKEFILE on)

#设置库目录
set(LIBRARY_DIRS “${CMAKE_SOURCE_DIR}/src/main/jniLibs”)

# 包含头文件目录
include_directories(src/main/cpp/include)

#添加 opencv 的动态库
add_library(
        libopencv_java4
        SHARED
        IMPORTED )

#指定库路径
set_target_properties(
        libopencv_java4
        IMPORTED_LOCATION
        “${LIBRARY_DIRS}/${ANDROID_ABI}/libopencv_java4.so” )

# 编译library
add_library( # 设置library名称
             opencv_learn

             # 设置library模式
             # SHARED模式会编译so文件，STATIC模式不会编译
             SHARED
        src/main/cpp/OpenCVLearn.cpp
             )

