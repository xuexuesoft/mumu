# Sources
file(GLOB_RECURSE SRCS_G "src/**.cpp" "src/**.h" "src/**.hpp" "src/**.c" "src/**.cc")
POCO_SOURCES_AUTO(SRCS ${SRCS_G})

# Headers
file(GLOB_RECURSE HDRS_G "include/**.h" "include/**.hpp")
POCO_HEADERS_AUTO(SRCS ${HDRS_G})

# Version Resource
if (MSVC AND BUILD_SHARED_LIBS)
    source_group("Resources" FILES ${PROJECT_SOURCE_DIR}/DLLVersion.rc)
    list(APPEND SRCS ${PROJECT_SOURCE_DIR}/DLLVersion.rc)
endif ()

# 这个宏是根据平台不同来选则加入的源文件,这里我们不使用
# POCO_SOURCES_AUTO_PLAT(SRCS WIN32
# 	src/WinRegistryConfiguration.cpp
# 	src/WinRegistryKey.cpp
# 	src/WinService.cpp
# )

# 把他们设置一个组,在vs下可能好看一些
vs_assign_source_group(SRCS)


# 定义一个子模块名
set(SUB_MODULE_NAME world)

message(STATUS "${SUB_MODULE_NAME}编译目标文件: ${SRCS}")

# 目前直接从这个库导出
add_library(${SUB_MODULE_NAME} SHARED ${SRCS})
add_library(${PROJECT_NAME}::${SUB_MODULE_NAME} ALIAS ${SUB_MODULE_NAME})

# 目标可以具有影响其构建方式的属性。
set_target_properties(${SUB_MODULE_NAME}
        PROPERTIES
        LINKER_LANGUAGE CXX
        VERSION ${SHARED_LIBRARY_VERSION} SOVERSION ${SHARED_LIBRARY_VERSION}
        #        PUBLIC_HEADER ${HDRS_G} #上面的头文件里设置了文件属性,这里是否还可以再设置呢?如果设置了它,那么使用者似乎在根目录可以include
        OUTPUT_NAME "${PROJECT_NAME}${SUB_MODULE_NAME}" #输出mumuwrold
        DEFINE_SYMBOL MUMU_WORLD_EXPORTS
)

target_include_directories(${SUB_MODULE_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE src
)

# 是否使用内部文件夹里的库
if (USE_EXTERNAL_DIR_LIB)
    # 如果是这样使用内部的库,那么不要执行install什么的,不然找不到项目里的其它库
    target_link_libraries(${SUB_MODULE_NAME} PUBLIC box2d)
else ()
    target_link_libraries(${SUB_MODULE_NAME} PUBLIC box2d::box2d)
    # 使用宏来规定install
    XUEXUE_INSTALL(${SUB_MODULE_NAME})
    XUEXUE_GENERATE_PACKAGE(${SUB_MODULE_NAME})
endif ()


if (ENABLE_TESTS)
    #  add_subdirectory(samples)
    add_subdirectory(testsuite)
endif ()
