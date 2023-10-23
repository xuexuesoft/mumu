//#include "TestEnvironment.h"
//
//#include "./crypto/cryptoTest.h"
//#include "./csharp/csharpTest.h"
//#include "./dnet/dnetTest.h"
//#include "./json/jsonTest.h"
//#include "xuexue/csharp/csharp.h"
//
//// windows的exe也可以具有导出函数,所以导出一下.
//#if defined(_WIN32) || defined(_WIN64)
//#    define XXTEST_EXPORT __declspec(dllexport)
//#else
//#    define XXTEST_EXPORT
//#endif
//
//#if __ANDROID__
//
//#    include <jni.h>
//#    include <android/log.h>
//#    include "CppUnit/TestRunner.h"
//#    include "poco/net/SocketsTestSuite.h"
//#    include "poco/net/TCPServerTest.h"
//#    include <sys/system_properties.h>
//
///**
// * 对接安卓的logcat
// * @param level
// * @param message
// */
//void DlogCallback(int level, const char *message)
//{
//    dlog_level dl = (dlog_level)level;
//    switch (dl) {
//    case dlog_level::trace:
//        __android_log_print(ANDROID_LOG_VERBOSE, "xxtest", "%s", message);
//        break;
//    case dlog_level::debug:
//        __android_log_print(ANDROID_LOG_DEBUG, "xxtest", "%s", message);
//        break;
//    case dlog_level::info:
//        __android_log_print(ANDROID_LOG_INFO, "xxtest", "%s", message);
//        break;
//    case dlog_level::warn:
//        __android_log_print(ANDROID_LOG_WARN, "xxtest", "%s", message);
//        break;
//    case dlog_level::err:
//        __android_log_print(ANDROID_LOG_ERROR, "xxtest", "%s", message);
//        break;
//    case dlog_level::critical:
//        __android_log_print(ANDROID_LOG_FATAL, "xxtest", "%s", message);
//        break;
//    case dlog_level::off:
//        __android_log_print(ANDROID_LOG_SILENT, "xxtest", "%s", message);
//        break;
//    }
//}
//
//std::string TestEnv::_workDir = "/data/data/com.dx.cpptest/cache/";
//
//#elif __APPLE__
//
//std::string TestEnv::_workDir = "./TestDir/";
//
//#else
//
//std::string TestEnv::_workDir = "./TestDir/";
//
//#endif
//
//std::string TestEnv::WorkDir()
//{
//    return _workDir;
//}
//
//void TestEnv::SetWorkDir(std::string &dir)
//{
//    if (dir.empty()) {
//        // 错误
//        return;
//    }
//    int last = int(dir.size()) - 1;
//
//    // 补全最后一个斜杠
//    if (dir[last] == '\\') {
//        _workDir = dir;
//        _workDir[last] = '/';
//    }
//    else if (dir[last] == '/') {
//        _workDir = dir;
//    }
//    else {
//        _workDir = dir + "/";
//    }
//}
//
//// 加上这个main函数还可以防止出现链接错误:
//// 无法解析的外部符号main，函数"int __cdecl invoke_main(void)"(?invoke_main@@YAHXZ)中引用了该符号
//int main(int argc, char *argv[])
//{
//#if defined(_WIN32) || defined(_WIN64)
//    system("chcp 65001"); // 测试了在windows下有效
//    dlog_init("log", "xuexueTest", dlog_init_relative::MODULE);
//#else
//    dlog_init("log", "xuexueTest");
//#endif
//    LogI("xuexueTest的测试启动...");
//
//    LogI("测试有:%s", PocoSocketTest::name().c_str());
//
//    ::testing::InitGoogleTest(&argc, argv);
//    // gtest takes ownership of the TestEnvironment ptr - we don't delete it.
//    ::testing::AddGlobalTestEnvironment(new TestEnv);
//    int res = RUN_ALL_TESTS();
//    LogI("xuexueTest的测试执行完毕,结果=%d", res);
//    return res;
//}
//
///**
// * @brief 设置一个日志回调指针.
// * @param logger 实际上可以直接使用dlog的指针类型.
// * @return
// */
//extern "C" XXTEST_EXPORT void __cdecl xxtSetLogger(DlogLoggerCallback logger)
//{
//    // loggerPtr = logger;
//    dlog_set_logger_function(logger);
//}
//
///**
// * @brief 外面设置一个工作目录,这个函数会把斜杠补全.
// * @param dir
// */
//extern "C" XXTEST_EXPORT void xxtSetWorkDir(char *dir)
//{
//    using namespace xuexue::csharp;
//    // 尝试创建这个工作目录文件夹
//    std::string path(dir);
//    if (!Directory::Exists(path)) {
//        Directory::createDirectory(path);
//    }
//
//    TestEnv::SetWorkDir(path);
//}
//
///**
// * @brief 运行测试,返回测试结果.
// * @param workdir 测试的工作文件夹
// * @param resultBuffer 返回的结果buffer
// * @param bufferLen 返回的结果buffer的长度
// */
//extern "C" XXTEST_EXPORT void xxtRunAllTests(char *workdir, char *resultBuffer, int bufferLen)
//{
//    xxtSetWorkDir(workdir);
//
//    using namespace xuexue::csharp;
//    // 造一个参数?
//    int argc = 1;
//    char *argv[] = {"X:/Temp/cmake/builds/bin/Debug/xxTest.exe"};
//#if __ANDROID__
//    dlog_set_logger_function(DlogCallback);
//#endif
//
//    dlog_init("log", "xuexueTest");
//    LogI("xuexueTest的测试启动...");
//
//    LogI("测试有:%s", PocoSocketTest::name().c_str());
//
//    // gtest的结果文件路径
//    std::string resultXml = std::string(workdir) + std::string("/result.xml");
//
//    //::testing::GTEST_FLAG(output) = "xml:/data/data/com.dx.cpptest/cache/result.xml";
//    ::testing::GTEST_FLAG(output) = (std::string("xml:") + resultXml).c_str();
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::AddGlobalTestEnvironment(new TestEnv);
//    int res = ::testing::UnitTest::GetInstance()->Run();
//    LogI("xuexueTest的测试执行完毕,结果=%d", res);
//    if (File::Exists(resultXml)) {
//
//        std::string testText = File::ReadAllText(resultXml);
//
//        // 在dlog中打印结果
//        std::vector<std::string> lines = String::Split(testText, {'\n'});
//        for (int i = 0; i < lines.size(); ++i) {
//            if (String::Contains(lines[i], std::string("failure message"))) {
//                LogMsg(dlog_level::warn, lines[i].c_str());
//            }
//            else {
//                LogMsg(dlog_level::info, lines[i].c_str());
//            }
//        }
//        // 返回字符串内容
//        int copyLen = testText.size() < bufferLen ? testText.size() : bufferLen; // 截取短的
//        memcpy(resultBuffer, testText.c_str(), copyLen);
//        // memcpy_s(resultBuffer, bufferLen, testText.c_str(), testText.size());
//    }
//}
//
//#if __ANDROID__
//
//extern "C" JNIEXPORT jstring JNICALL
//Java_com_dx_cpptest_MainActivity_RunAllTests(JNIEnv *env, jobject thiz)
//{
//    // TODO: implement RunAllTests()
//    __android_log_print(ANDROID_LOG_INFO, "xxtest", "cxx部分启动!");
//
//    // 造一个参数?
//    int argc = 1;
//    char *argv[] = {"X:\\Temp\\cmake\\builds\\bin\\Debug\\xxTest.exe"};
//
//    dlog_set_logger_function(DlogCallback);
//    dlog_init("log", "xuexueTest");
//    LogI("xuexueTest的测试启动...");
//    //    Environment.getDataDirectory():      /data
//    //    Context.getCacheDir():               /data/data/com.learn.test/cache
//    //    Context.getFilesDir():               /data/data/com.learn.test/files
//    //    Context.getFileStreamPath(""):       /data/data/com.learn.test/files
//    //    Context.getFileStreamPath("test"):   /data/data/com.learn.test/files/test
//    // 测试一下cache文件夹内容读写
//    using namespace xuexue::csharp;
//    std::string testFilePath = "/storage/emulated/0/Download/test.txt";
//    File::WriteAllText(testFilePath, "这是一些测试文本!");
//    std::string text = File::ReadAllText(testFilePath);
//    if (!text.empty())
//        LogI("读出文本内容:%s", text.c_str());
//
//    char m_szDevID[512];
//    __system_property_get("ro.serialno", m_szDevID);
//    LogI("m_szDevID=%s", m_szDevID);
//
//    // 读取机型
//    char m_szDevModel[512];
//    __system_property_get("ro.product.model", m_szDevModel);
//    LogI("m_szDevModel=%s", m_szDevModel);
//
//    // 读取sdk版本
//    char m_szSdkVer[512];
//    __system_property_get("ro.build.version.sdk", m_szSdkVer);
//    LogI("m_szSdkVer=%s", m_szSdkVer);
//
//    //    std::vector<std::string> args;
//    //    args.push_back("POCOSocket.exe");
//    //    args.push_back("-all");
//    //    CppUnit::TestRunner runner;
//    //    runner.addTest("SocketsTestSuite", SocketsTestSuite::suite());
//    //    CppUnitPocoExceptionText(exc);
//    //    runner.run(args, exc) ? 0 : 1;
//
//    //    TCPServerTest test("TCPServerTest");
//    //    test.setUp();
//    //    test.testOneConnection();
//    //    test.testTwoConnections();
//    //    test.testMultiConnections();
//    //    test.testThreadCapacity();
//    //    test.testFilter();
//    //    test.tearDown();
//    //    std::string testOutputFile = "/data/data/com.dx.cpptest/cache/test.txt";
//    ::testing::GTEST_FLAG(output) = "xml:/data/data/com.dx.cpptest/cache/result.xml";
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::AddGlobalTestEnvironment(new TestEnv);
//    int res = ::testing::UnitTest::GetInstance()->Run();
//    LogI("xuexueTest的测试执行完毕,结果=%d", res);
//    if (File::Exists("/data/data/com.dx.cpptest/cache/result.xml")) {
//        // 拷贝测试结果文件到公共文件夹里去
//        File::Copy("/data/data/com.dx.cpptest/cache/result.xml", "/storage/emulated/0/Download/result.xml");
//
//        std::string testText = File::ReadAllText("/data/data/com.dx.cpptest/cache/result.xml");
//
//        std::vector<std::string> lines = String::Split(testText, {'\n'});
//        for (int i = 0; i < lines.size(); ++i) {
//            if (String::Contains(lines[i], std::string("failure message"))) {
//                LogMsg(dlog_level::warn, lines[i].c_str());
//            }
//            else {
//                LogMsg(dlog_level::info, lines[i].c_str());
//            }
//        }
//        // 返回字符串内容
//        return env->NewStringUTF(testText.c_str());
//    }
//    return env->NewStringUTF("没有测试结果文件");
//}
//
//#endif
