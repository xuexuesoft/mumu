//#pragma once
//#include "xuexue/dlog/dlog.h"
//
//#include "gtest/gtest.h"
//
//#include <chrono>
//
///**
// * @brief 来自: https://stackoverflow.com/questions/30593762/how-to-initialize-constant-string-for-multiple-tests-in-google-test
// */
//class TestEnv : public ::testing::Environment
//{
//  public:
//    // 做一个静态函数让测试方能够调用
//    static std::string getStartTime()
//    {
//        static const std::string timestamp =
//            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
//        return timestamp;
//    }
//
//    /**
//     * @brief 工作文件夹路径,末尾带斜杠/,如./
//     * @return
//     */
//    static std::string WorkDir();
//
//    /**
//     * @brief 设置路径,这个函数会把斜杠补全.
//     * @param dir
//     */
//    static void SetWorkDir(std::string& dir);
//
//    // Initialise the timestamp.
//    virtual void SetUp()
//    {
//        LogI("TestEnv():SetUp执行!");
//    }
//
//    virtual void TearDown()
//    {
//        LogI("TestEnv():TearDown执行!");
//    }
//
//  private:
//    static std::string _workDir;
//};
