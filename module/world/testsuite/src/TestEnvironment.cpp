#include "gtest/gtest.h"
#include <chrono>

#include "mumu/world/Export.h"
#include "mumu/world/Log.h"

// 来自: https://stackoverflow.com/questions/30593762/how-to-initialize-constant-string-for-multiple-tests-in-google-test

std::string currentDateTime()
{
    return std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
}

class TestEnvironment : public ::testing::Environment
{
  public:
    // 做一个静态函数让测试方能够调用
    static std::string getStartTime()
    {
        static const std::string timestamp = currentDateTime();
        return timestamp;
    }

    // Initialise the timestamp.
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

using namespace xuexue;

static void OnLogger(log_level level, const char* message)
{
    switch (level) {
    case log_level::trace:
        printf("[trace] %s\n", message);
        break;
    case log_level::debug:
        printf("[debug] %s\n", message);
        break;
    case log_level::info:
        printf("[info] %s\n", message);
        break;
    case log_level::warn:
        printf("[warn] %s\n", message);
        break;
    case log_level::err:
        printf("[err] %s\n", message);
        break;
    case log_level::critical:
        printf("[critical] %s\n", message);
        break;
    case log_level::off:
        printf("[off] %s\n", message);
        break;
    }
}

int main(int argc, char* argv[])
{
    // 设置日志回调
    xuexue::LogUtil::SetLoggerFunction(OnLogger);

    ::testing::InitGoogleTest(&argc, argv);
    // gtest takes ownership of the TestEnvironment ptr - we don't delete it.
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}