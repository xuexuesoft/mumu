//
// Created by dx on 2023/10/23.
//

#include "mumu/world/Log.h"
#include <vector>

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

class Logger
{
  public:
    static Logger* GetInst()
    {
        return m_pInstance;
    }

    /**
     * 是否需要打日志
     * @param level
     * @return
     */
    bool IsNeedLog(dlog_level level) const
    {
        if (loggerCallback == nullptr) {
            return false;
        }
        if ((int)level >= levelThr) {
            return true;
        }
        return false;
    }

    void Log(dlog_level level, const char* msg) const
    {
        // 只执行回调
        loggerCallback(level, msg);
    }

    // 对接外面的函数指针
    LoggerCallback loggerCallback = nullptr;

    // 默认等级门限
    int levelThr = 2;

  private:
    // 单例
    static Logger* m_pInstance;
};
Logger* Logger::m_pInstance = new Logger();

/**
 * 设置回调函数指针进来
 */
extern "C" DLOG_EXPORT void __cdecl log_set_logger_function(LoggerCallback fp)
{
    Logger::GetInst()->loggerCallback = fp;
}

/**
 * Logs an info.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogI(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(dlog_level::info)) {
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
    Logger::GetInst()->Log(dlog_level::info, buf.data());
}

/**
 * Logs a warring.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogW(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(dlog_level::warn)) {
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
    Logger::GetInst()->Log(dlog_level::warn, buf.data());
}

/**
 * Logs an error.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogE(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(dlog_level::err)) {
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
    Logger::GetInst()->Log(dlog_level::err, buf.data());
}

/**
 * Logs a debug.
 *
 * @param  strFormat Describes the format to use.
 * @param  ...       Variable arguments providing additional information.
 */
extern "C" DLOG_EXPORT void __cdecl LogD(const char* strFormat, ...)
{
    if (!Logger::GetInst()->IsNeedLog(dlog_level::debug)) {
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
    Logger::GetInst()->Log(dlog_level::debug, buf.data());
}

} // namespace xuexue