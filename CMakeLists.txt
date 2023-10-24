cmake_minimum_required(VERSION 3.22)

project(mumu CXX)

# 规定项目版本
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(PROJECT_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

#set(BUILD_SHARED_LIBS OFF CACHE BOOL "定义BUILD_SHARED_LIBS=OFF" FORCE)

# 开始的时候输出一下看看...
message(STATUS "总工程${PROJECT_NAME}的CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "总工程${PROJECT_NAME}的CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

# PLATFORM是一个工具链传入的自己的定义,这里我们不使用
message(STATUS "总工程${PROJECT_NAME}的PLATFORM = ${PLATFORM}")

# 载入从poco库中拷的一份cmake工具
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# 加入功能性的宏
include(PocoMacros)
include(xuexueMacros)

# 修复一下install文件夹路径
xuexue_set_cmake_default_dir()

# 设置C++17吧
include(CXX1x)
check_for_cxx17_compiler(CXX17_COMPILER)
if (CXX17_COMPILER)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
else ()
    message(FATAL_ERROR "Compiler does not support C++17.")
endif ()


# 设置macos的编译通用的
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "macOS编译通用的两种指令" FORCE)
#set(CMAKE_SYSTEM_PROCESSOR "arm64;x86_64" CACHE STRING "" FORCE)


# 测试相关
option(ENABLE_TESTS "Set to OFF|ON (default is ON) 是否开启测试" ON)
if (ENABLE_TESTS)
    # 这个CTest会搞出来一大堆工程配置,暂时关闭吧
    #    include(CTest)
    #    enable_testing()
    message(STATUS "工程${PROJECT_NAME}编译 - 启用测试")
else ()
    message(STATUS "工程${PROJECT_NAME}编译 - 不启用测试")
endif ()


# 在windows平台定义dll或者库的后缀(这里我们目前用不上)
#include(DefinePlatformSpecific)


set(USE_EXTERNAL_DIR_LIB ON CACHE BOOL "使用external文件夹中的库(用于开发模式)=ON" FORCE)

if (USE_EXTERNAL_DIR_LIB)
    # 如果是这样的就直接把依赖库的源码添加进来,这是用于开发的模式
    add_subdirectory(external)
else ()
    # 否则的话就需要去find_package
    find_package(box2d REQUIRED)
    if (ENABLE_TESTS)
        find_package(GTest REQUIRED)
    endif ()
endif ()

add_subdirectory(module/world)

#install(TARGETS mumu)

# 输出一些当前的构造设置
xuexue_output_build_status()