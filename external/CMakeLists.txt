cmake_minimum_required(VERSION 3.8)

message(STATUS "配置box2d库...")
set(BOX2D_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BOX2D_BUILD_TESTBED ON CACHE BOOL "" FORCE)
add_subdirectory("box2d")

message(STATUS "配置gtest库...")
set(BUILD_GMOCK OFF CACHE BOOL "BUILD_GMOCK OFF" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "INSTALL_GTEST OFF" FORCE)
add_subdirectory("googletest")

# 随便的设置一下吧
set(BOX2D_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/box2d/include)
set(GEST_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)

include_directories(${BOX2D_INCLUDE_PATH})
include_directories(${GEST_INCLUDE_PATH})
