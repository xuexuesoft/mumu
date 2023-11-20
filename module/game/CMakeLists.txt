# 定义一个子模块名
set(SUB_MODULE_NAME game)

# 头文件
file(GLOB_RECURSE INCLUDE_LIST "include/**.h" "include/**.hpp")
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR}/include/mumu ${INCLUDE_LIST})

# 源文件
file(GLOB_RECURSE SOURCE_LIST "src/**.cpp" "src/**.c" "src/**.h" "src/**.hpp")
assign_source_group(${CMAKE_CURRENT_SOURCE_DIR}/src ${SOURCE_LIST})

# 如果是win平台,加入windows平台的文件
if (WIN32)
    FILE(GLOB_RECURSE SOURCE_WIN_LIST "Win/**.cpp" "Win/**.h" "Win/**.hpp" "Win/**.c")
    assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ${SOURCE_WIN_LIST})
    list(APPEND SOURCE_LIST ${SOURCE_WIN_LIST})
endif ()

# dll.rc
if (MSVC AND BUILD_SHARED_LIBS)
    source_group("Resources" FILES ${PROJECT_SOURCE_DIR}/DLLVersion.rc)
    list(APPEND SOURCE_LIST ${PROJECT_SOURCE_DIR}/DLLVersion.rc)
endif ()

# 把头文件也加进source去,这样在vs工程里可以更方便的显示
list(APPEND SOURCE_LIST ${INCLUDE_LIST})

# 如果是共享库那么要定义这个,否则下面的设置target属性的时候会没有值.
set(SHARED_LIBRARY_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR})

message(STATUS "${SUB_MODULE_NAME}编译目标文件: ${SOURCE_LIST}")
# 目前直接从这个库导出
add_library(${SUB_MODULE_NAME} SHARED ${SOURCE_LIST})
add_library(${PROJECT_NAME}::${SUB_MODULE_NAME} ALIAS ${SUB_MODULE_NAME})

# 目标可以具有影响其构建方式的属性。
set_target_properties(${SUB_MODULE_NAME}
        PROPERTIES
        LINKER_LANGUAGE CXX
        # 目前先不导出这个版本吧
        #VERSION ${SHARED_LIBRARY_VERSION}
        #SOVERSION ${SHARED_LIBRARY_VERSION}
        #PUBLIC_HEADER ${HDRS_G} #上面的头文件里设置了文件属性,这里是否还可以再设置呢?如果设置了它,那么使用者似乎在根目录可以include
        OUTPUT_NAME "${PROJECT_NAME}${SUB_MODULE_NAME}" #输出mumugame
        DEFINE_SYMBOL MUMU_WORLD_EXPORTS
)

target_include_directories(${SUB_MODULE_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE src
)

# 是否使用内部文件夹里的库
if (USE_INTERNAL_DEPENDENCY_LIB)
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
