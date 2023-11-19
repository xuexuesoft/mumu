#===============================================================================
# 这个函数在VS工程里生成一个文件路径
function(vs_assign_source_group)
    foreach (_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else ()
            set(_source_rel "${_source}")
        endif ()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        #这个表示在VS里划分一个组
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach ()
endfunction(vs_assign_source_group)

#===============================================================================
# 有时候这几个值没有设置,导致install的时候出错.
function(xuexue_set_cmake_default_dir)
    message(STATUS "进入函数 set_cmake_install_dir_default()...")
    if (NOT CMAKE_INSTALL_BINDIR)
        message(STATUS "工程${PROJECT_NAME}的 CMAKE_INSTALL_BINDIR 未设置值,这里设置为bin")
        set(CMAKE_INSTALL_BINDIR "bin")
    endif ()
    if (NOT CMAKE_INSTALL_LIBDIR)
        message(STATUS "工程${PROJECT_NAME}的 CMAKE_INSTALL_LIBDIR 未设置值,这里设置为lib")
        set(CMAKE_INSTALL_LIBDIR "lib")
    endif ()
    if (NOT CMAKE_INSTALL_INCLUDEDIR)
        message(STATUS "工程${PROJECT_NAME}的 CMAKE_INSTALL_INCLUDEDIR 未设置值,这里设置为include")
        set(CMAKE_INSTALL_INCLUDEDIR "include")
    endif ()

    # 构建时将所有ARCHIVE目标文件放在哪里
    if (NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
        message(STATUS "工程${PROJECT_NAME}的 CMAKE_LIBRARY_OUTPUT_DIRECTORY 未设置值,这里设置为lib")
        set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_BINARY_DIR}/lib)
    endif ()
    if (NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
        message(STATUS "工程${PROJECT_NAME}的 CMAKE_ARCHIVE_OUTPUT_DIRECTORY 未设置值,这里设置为lib")
        set(CMAKE_INSTALL_INCLUDEDIR ${CMAKE_BINARY_DIR}/lib)
    endif ()
    if (NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
        message(STATUS "工程${PROJECT_NAME}的 CMAKE_RUNTIME_OUTPUT_DIRECTORY 未设置值,这里设置为bin")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    endif ()

endfunction(xuexue_set_cmake_default_dir)

# 输出一些当前的构造设置
function(xuexue_output_build_status)
    message(STATUS "CMake ${CMAKE_VERSION} 成功配置 ${PROJECT_NAME} 使用 ${CMAKE_GENERATOR} ")
    message(STATUS "${PROJECT_NAME} 工程版本: ${PROJECT_VERSION}")
    if (BUILD_SHARED_LIBS)
        message(STATUS "[cmake] 构建动态库")
    else ()
        message(STATUS "[cmake] 构建静态库")
    endif ()

    if (${CMAKE_INSTALL_PREFIX} MATCHES "^[/].*")
        message(WARNING "项目${PROJECT_NAME}安装目标PREFIX路径:${CMAKE_INSTALL_PREFIX},可能把系统环境搞乱...")
    else ()
        message(STATUS "[cmake] 项目${PROJECT_NAME}安装目标PREFIX路径:${CMAKE_INSTALL_PREFIX}")
    endif ()

    message(STATUS "[cmake] 安装目标LIBDIR路径: ${CMAKE_INSTALL_LIBDIR}")

    if (CMAKE_TOOLCHAIN_FILE)
        message(STATUS "[cmake] 使用工具链:      ${CMAKE_TOOLCHAIN_FILE}")
    endif ()
    message(STATUS "[cmake] Build for OS type:      ${CMAKE_SYSTEM_NAME}")
    message(STATUS "[cmake] Build for OS version:   ${CMAKE_SYSTEM_VERSION}")
    message(STATUS "[cmake] Build for CPU type:     ${CMAKE_SYSTEM_PROCESSOR}")
    message(STATUS "[cmake] Build type:             ${CMAKE_BUILD_TYPE}")
    string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
    message(STATUS "[cmake] Build with cxx flags:   ${CMAKE_CXX_FLAGS_${BUILD_TYPE}} ${CMAKE_CXX_FLAGS}")
    message(STATUS "[cmake] Build with c flags:     ${CMAKE_C_FLAGS_${BUILD_TYPE}} ${CMAKE_C_FLAGS}")
endfunction(xuexue_output_build_status)

#===============================================================================
# 给一个模块生成package.
#
#  XUEXUE_GENERATE_PACKAGE - 生成 *Config.cmake
#    Usage: XUEXUE_GENERATE_PACKAGE(target_name)
#      INPUT:
#           target_name             the name of the target. e.g. Foundation for PocoFoundation
#    Example: POCO_GENERATE_PACKAGE(Foundation)
macro(XUEXUE_GENERATE_PACKAGE target_name)
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}ConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY AnyNewerVersion
    )
    if ("${CMAKE_VERSION}" VERSION_LESS "3.0.0")
        if (NOT EXISTS "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Targets.cmake")
            export(TARGETS "${target_name}" APPEND
                    FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Targets.cmake"
                    NAMESPACE "${PROJECT_NAME}::"
            )
        endif ()
    else ()
        export(EXPORT "${target_name}Targets"
                FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Targets.cmake"
                NAMESPACE "${PROJECT_NAME}::"
        )
    endif ()
    # configure_file("cmake/Poco${target_name}Config.cmake" 去掉原来的Poco
    configure_file("cmake/${target_name}Config.cmake"
            "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Config.cmake"
            @ONLY
    )

    # Set config script install location in a location that find_package() will
    # look for, which is different on MS Windows than for UNIX
    # Note: also set in root CMakeLists.txt
    if (WIN32)
        set(PocoConfigPackageLocation "cmake")
    else ()
        set(PocoConfigPackageLocation "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
    endif ()

    install(
            EXPORT "${target_name}Targets"
            FILE "${PROJECT_NAME}${target_name}Targets.cmake"
            NAMESPACE "${PROJECT_NAME}::"
            DESTINATION "${PocoConfigPackageLocation}"
    )

    install(
            FILES
            "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}Config.cmake"
            "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}${target_name}ConfigVersion.cmake"
            DESTINATION "${PocoConfigPackageLocation}"
            COMPONENT Devel
    )

endmacro()

#===============================================================================
# 纯头文件的宏的
macro(XUEXUE_INSTALL_ONLY_HEADER target_name)
    install(
            DIRECTORY include/*
            DESTINATION include
            COMPONENT Devel
            PATTERN ".svn" EXCLUDE
    )

    #    install(
    #            TARGETS "${target_name}" EXPORT "${target_name}Targets"
    #            # LIBRARY DESTINATION lib${LIB_SUFFIX}
    #            # ARCHIVE DESTINATION lib${LIB_SUFFIX}
    #            RUNTIME DESTINATION bin
    #            BUNDLE DESTINATION bin
    #            INCLUDES DESTINATION include
    #    )
endmacro()

#===============================================================================
# Macros for simplified installation
#
#  POCO_INSTALL - Install the given target
#    Usage: POCO_INSTALL(target_name)
#      INPUT:
#           target_name             the name of the target. e.g. Foundation for PocoFoundation
#    Example: POCO_INSTALL(Foundation)
macro(XUEXUE_INSTALL target_name)
    install(
            # 这里的我的库是从include/Poco修改为了include/xuexue
            DIRECTORY include/${PROJECT_NAME}
            DESTINATION include
            COMPONENT Devel
            PATTERN ".svn" EXCLUDE
    )

    #根据Target属性配置执行的安装
    install(
            TARGETS "${target_name}" EXPORT "${target_name}Targets"
            LIBRARY DESTINATION lib${LIB_SUFFIX}
            ARCHIVE DESTINATION lib${LIB_SUFFIX}
            RUNTIME DESTINATION bin
            BUNDLE DESTINATION bin
            INCLUDES DESTINATION include
            PUBLIC_HEADER DESTINATION include
    )

    if (MSVC)
        # install the targets pdb
        XUEXUE_INSTALL_PDB(${target_name})
    endif ()

endmacro()


#  POCO_INSTALL_PDB - Install the given target's companion pdb file (if present)
#    Usage: POCO_INSTALL_PDB(target_name)
#      INPUT:
#           target_name             the name of the target. e.g. Foundation for PocoFoundation
#    Example: POCO_INSTALL_PDB(Foundation)
#
#    This is an internal macro meant only to be used by POCO_INSTALL.
macro(XUEXUE_INSTALL_PDB target_name)
    get_property(type TARGET ${target_name} PROPERTY TYPE)
    if ("${type}" STREQUAL "SHARED_LIBRARY" OR "${type}" STREQUAL "EXECUTABLE")
        install(
                FILES $<TARGET_PDB_FILE:${target_name}>
                DESTINATION bin
                COMPONENT Devel
                OPTIONAL
        )
    endif ()
endmacro()

#===============================================================================
# 这个函数在VS工程里生成一个文件路径,让vs编辑器里的目录更美观.
# CUR_ROOT_DIR [in]: 文件路径的相对ROOT路径
function(assign_source_group CUR_ROOT_DIR)
    foreach (_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            # 给它一个相对目标
            file(RELATIVE_PATH _source_rel "${CUR_ROOT_DIR}" "${_source}")
        else ()
            set(_source_rel "${_source}")
        endif ()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        #这个表示在VS里划分一个组
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach ()
endfunction(assign_source_group)