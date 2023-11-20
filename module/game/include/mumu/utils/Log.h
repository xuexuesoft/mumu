#pragma once

// 它是定义vs编译器使用utf-8,现在整个dlog统一应该使用utf-8作为输出.注意文件需要保存成UTF8带BOM
#if defined(_WIN32) || defined(_WIN64)
#    pragma execution_character_set("utf-8")
#endif

namespace xuexue {

// 给用户使用的LogSeverity定义,目前和spdlog里的定义一致,但是只使用debug,info,warn,err
enum class log_level : int
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
typedef void (*LoggerCallback)(log_level level, const char* message);

/**
 * @brief 简单的日志系统,如果这个系统没有对接一个日志系统,那么不会有输出.
 */
class LogUtil
{
  public:
    /**
     * 设置一个外部对接其他日志系统的回调(如第三方控制台等等),注意每次close日志系统会清空这个设置,之后需要重新设置一次.
     *
     * @param  fp 函数指针.
     */
    static void SetLoggerCallback(LoggerCallback fp);

    /**
     * 设置输出日志的等级门限,这样可以减少格式化开销.
     * @param thr
     */
    static void SetOutputLevelThr(log_level thr);

    /**
     * Logs an info.
     *
     * @param  strFormat Describes the format to use.
     * @param  ...       Variable arguments providing additional information.
     */
    static void Info(const char* strFormat, ...);

    /**
     * Logs a warring.
     *
     * @param  strFormat Describes the format to use.
     * @param  ...       Variable arguments providing additional information.
     */
    static void Warring(const char* strFormat, ...);

    /**
     * Logs an error.
     *
     * @param  strFormat Describes the format to use.
     * @param  ...       Variable arguments providing additional information.
     */
    static void Error(const char* strFormat, ...);

    /**
     * Logs a debug.
     *
     * @param  strFormat Describes the format to use.
     * @param  ...       Variable arguments providing additional information.
     */
    static void Debug(const char* strFormat, ...);
};
} // namespace xuexue

#ifndef DISABLE_DLOG_CFUN_MACRO
// 代码文件必须要加bom头,然后换行符改成crlf,否则MSVC编译器会报错C2001:常量中有换行符
#    define LogD(...) xuexue::LogUtil::Debug(__VA_ARGS__)
#    define LogI(...) xuexue::LogUtil::Info(__VA_ARGS__)
#    define LogW(...) xuexue::LogUtil::Warring(__VA_ARGS__)
#    define LogE(...) xuexue::LogUtil::Error(__VA_ARGS__)
// #    define LogD(format, ...) xuexue::LogUtil::Debug(format, ##__VA_ARGS__)
// #    define LogI(format, ...) xuexue::LogUtil::Info(format, ##__VA_ARGS__)
// #    define LogW(format, ...) xuexue::LogUtil::Warring(format, ##__VA_ARGS__)
// #    define LogE(format, ...) xuexue::LogUtil::Error(format, ##__VA_ARGS__)
#endif
