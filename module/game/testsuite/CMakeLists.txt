cmake_minimum_required(VERSION 3.8 FATAL_ERROR)


#这里会搜索到build文件夹下面的一个cpp文件,所以增加一个*Test.cpp的约束
FILE(GLOB_RECURSE SOURCE_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**.h")
message(STATUS "SOURCE_LIST = ${SOURCE_LIST}")


find_package(Threads)
# 载入GoogleTest库
#find_package(GTest REQUIRED)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
# 这个设置的作用没研究=。=
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 设置Test项目名
set(TEST_NAME "${SUB_MODULE_NAME}Test")

add_executable(${TEST_NAME} ${SOURCE_LIST})
target_include_directories(${TEST_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../external>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)


if (USE_INTERNAL_DEPENDENCY_LIB)
    target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main ${SUB_MODULE_NAME} ${CMAKE_THREAD_LIBS_INIT})
    # 可能需要gtest头文件
    include_directories("${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")
else ()
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest GTest::gtest_main ${SUB_MODULE_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif ()
# 加入GTest::gtest会自动添加头文件

