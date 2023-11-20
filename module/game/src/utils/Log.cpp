#include "mumu/utils/Log.h"

#include <vector>
#include <cstdarg>

namespace xuexue {

// enum class dlog_level
//{
//     trace = 0,
//     debug = 1,
//     info = 2,
//     warn = 3,
//     err = 4,
//     critical = 5,
//     off = 6,
// };

// 一条日志的默认预估长度
#define DEBUG_LOG_BUFF_SIZE 128

/**
 * @brief 内部的日志实例.
 */
class Logger
{
  public:
    static Logger* GetInst()
    {
        return m_pInstance;
    }

    /**
     * 判断当前日志等级是否需要输出日志.
     * @param level
     * @return
     */
    bool IsNeedLog(log_level level) const
    {
        if (loggerCallback == nullptr) {
            return false;
        }
        if ((int)level >= levelThr) {
            return true;
        }
        return false;
    }

    void Log(log_level level, const char* msg) const
    {
        // 只执行回调,如果这个系统没有对接一个日志系统,那么不会有输出.
        loggerCallback(level, msg);
    }

    // 对接外面的函数指针
    LoggerCallback loggerCallback = nullptr;

    // 默认等级门限
    int levelThr = (int)log_level::debug;

  private:
    // 单例
    static Logger* m_pInstance;
};
Logger* Logger::m_pInstance = new Logger();

/**
 * 设置回调函数指针进来
 */
void LogUtil::SetLoggerCallback(LoggerCallback fp)
{
    Logger::GetInst()->loggerCallback = fp;
}

/**
 * Logs an info.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
void LogUtil::Info(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(log_level::info)) {
        return;
    }
    std::vector<char> buf(DEBUG_LOG_BUFF_SIZE, '\0');
    int ret = 0;
    va_list arg_ptr;
    va_start(arg_ptr, strFormat);
    // 最多执行4次增加buff长度
    for (size_t count = 0; count < 4; count++) {
        // vsnprintf的返回是不包含\0的预留位置的
        ret = vsnprintf(buf.data(), buf.size(), strFormat, arg_ptr);
        if (ret <= 0) {
            break; // 编码失败
        }
        else if (ret >= buf.size()) {
            // buff长度不够
            buf.resize((size_t)ret * 4, '\0');
            // 在GCC平台需要重新生成一下arg_ptr
            va_end(arg_ptr);
            va_start(arg_ptr, strFormat);
        }
        else {
            // 编码成功
            break;
        }
    }
    va_end(arg_ptr);
    Logger::GetInst()->Log(log_level::info, buf.data());
}

/**
 * Logs a warring.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
void LogUtil::Warring(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(log_level::warn)) {
        return;
    }
    std::vector<char> buf(DEBUG_LOG_BUFF_SIZE, '\0');
    int ret = 0;
    va_list arg_ptr;
    va_start(arg_ptr, strFormat);
    // 最多执行4次增加buff长度
    for (size_t count = 0; count < 4; count++) {
        // vsnprintf的返回是不包含\0的预留位置的
        ret = vsnprintf(buf.data(), buf.size(), strFormat, arg_ptr);
        if (ret <= 0) {
            break; // 编码失败
        }
        else if (ret >= buf.size()) {
            // buff长度不够
            buf.resize((size_t)ret * 4, '\0');
            // 在GCC平台需要重新生成一下arg_ptr
            va_end(arg_ptr);
            va_start(arg_ptr, strFormat);
        }
        else {
            // 编码成功
            break;
        }
    }
    va_end(arg_ptr);
    Logger::GetInst()->Log(log_level::warn, buf.data());
}

/**
 * Logs an error.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
void LogUtil::Error(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(log_level::err)) {
        return;
    }
    std::vector<char> buf(DEBUG_LOG_BUFF_SIZE, '\0');
    int ret = 0;
    va_list arg_ptr;
    va_start(arg_ptr, strFormat);
    // 最多执行4次增加buff长度
    for (size_t count = 0; count < 4; count++) {
        // vsnprintf的返回是不包含\0的预留位置的
        ret = vsnprintf(buf.data(), buf.size(), strFormat, arg_ptr);
        if (ret <= 0) {
            break; // 编码失败
        }
        else if (ret >= buf.size()) {
            // buff长度不够
            buf.resize((size_t)ret * 4, '\0');
            // 在GCC平台需要重新生成一下arg_ptr
            va_end(arg_ptr);
            va_start(arg_ptr, strFormat);
        }
        else {
            // 编码成功
            break;
        }
    }
    va_end(arg_ptr);
    Logger::GetInst()->Log(log_level::err, buf.data());
}

/**
 * Logs a debug.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
void LogUtil::Debug(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(log_level::debug)) {
        return;
    }
    std::vector<char> buf(DEBUG_LOG_BUFF_SIZE, '\0');
    int ret = 0;
    va_list arg_ptr;
    va_start(arg_ptr, strFormat);
    // 最多执行4次增加buff长度
    for (size_t count = 0; count < 4; count++) {
        // vsnprintf的返回是不包含\0的预留位置的
        ret = vsnprintf(buf.data(), buf.size(), strFormat, arg_ptr);
        if (ret <= 0) {
            break; // 编码失败
        }
        else if (ret >= buf.size()) {
            // buff长度不够
            buf.resize((size_t)ret * 4, '\0');
            // 在GCC平台需要重新生成一下arg_ptr
            va_end(arg_ptr);
            va_start(arg_ptr, strFormat);
        }
        else {
            // 编码成功
            break;
        }
    }
    va_end(arg_ptr);
    Logger::GetInst()->Log(log_level::debug, buf.data());
}

void LogUtil::SetOutputLevelThr(log_level thr)
{
    Logger::GetInst()->levelThr = (int)thr;
}

} // namespace xuexue
