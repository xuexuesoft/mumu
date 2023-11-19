#pragma once

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

class LogUtil
{
  public:

    /**
     * 设置输出日志的等级门限,这样可以减少格式化开销.
     * @param thr
     */
    static void SetOutputLevelThr(log_level thr);

    /**
     * 设置一个外部对接其他日志系统的回调(如第三方控制台等等),注意每次close日志系统会清空这个设置,之后需要重新设置一次.
     *
     * @param  fp 函数指针.
     */
    static void SetLoggerCallback(LoggerCallback fp);

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
#    define LogD(format, ...) xuexue::LogUtil::Debug(format, ##__VA_ARGS__)
#    define LogI(format, ...) xuexue::LogUtil::Info(format, ##__VA_ARGS__)
#    define LogW(format, ...) xuexue::LogUtil::Warring(format, ##__VA_ARGS__)
#    define LogE(format, ...) xuexue::LogUtil::Error(format, ##__VA_ARGS__)
#endif