#pragma once

// --------------------- windows ---------------------
// 由三个定义来控制,构建时会根据是否是共享库定义DLOG_DLL_EXPORTS或DLOG_STATIC,
// 使用该库的其他项目会由这个库的conan文件加入DLOG_STATIC或DLOG_DLL的定义.
#if defined(_WIN32) || defined(_WIN64)
// 如果是库自身dll构建,导出dll
#    if defined(DLOG_DLL_EXPORTS) // 导出库使用dll模式
#        define DLOG_EXPORT __declspec(dllexport)
#        define DLOG__LOCAL
// 如果是引用该dll
#    elif defined DLOG_DLL_IMPORT
#        define DLOG_EXPORT __declspec(dllimport)
// #        pragma comment(lib, "dlog.lib")
#    else
// 静态使用
#        define DLOG_EXPORT
#        define DLOG__LOCAL
#    endif

// 它是定义vs编译器使用utf-8,现在整个dlog统一应该使用utf-8作为输出.注意文件需要保存成UTF8带BOM
#    ifndef DLOG_NO_UTF8
#        pragma execution_character_set("utf-8")
#    endif

// ---------- 非VC的编译器那么先不区分dllimport ---------------
#else
#    define DLOG_EXPORT __attribute__((visibility("default")))
#    define DLOG__LOCAL __attribute__((visibility("hidden")))
#
#    define __cdecl // 默认是，加上了反而有warning __attribute__((__cdecl__))
#endif

// 给用户使用的LogSeverity定义,目前和spdlog里的定义一致,但是只使用debug,info,warn,err
enum class dlog_level : int
{
    trace = 0,
    debug = 1,
    info = 2,
    warn = 3,
    err = 4,
    critical = 5,
    off = 6,
};

// 日志回调函数指针类型,message为日志的原始文本
typedef void (*LoggerCallback)(dlog_level level, const char* message);

/**
 * 设置一个外部对接其他日志系统的回调(如第三方控制台等等),注意每次close日志系统会清空这个设置,之后需要重新设置一次.
 *
 * @param  fp 函数指针.
 */
extern "C" DLOG_EXPORT void __cdecl log_set_logger_function(LoggerCallback fp);

/**
 * Logs an info.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogI(const char* strFormat, ...);

/**
 * Logs a warring.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogW(const char* strFormat, ...);

/**
 * Logs an error.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogE(const char* strFormat, ...);

/**
 * Logs a debug.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogD(const char* strFormat, ...);