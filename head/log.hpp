/*
 * This file is part of the software and assets of HK ZXOUD LIMITED.
 * @copyright (c) HK ZXOUD LIMITED https://www.zxoud.com
 * Author: yushou-cell(email:2354739167@qq.com)
 * create: 20240620
 * FilePath: /zlink/head/log.hpp
 * Description: output infos, warnings, errors and fatals log to terminal
 */
#pragma once
#include "system.hpp"

struct LogMQ : public NonCopyable
{
    inline LogMQ(const char *execFileName)
    {
        std::filesystem::path dirPath("./Log");
        if (!std::filesystem::exists(dirPath))
        {
            std::filesystem::create_directory(dirPath);
        }
        FLAGS_logbufsecs = 1;
        google::InitGoogleLogging(execFileName);
        FLAGS_max_log_size = 10;
        FLAGS_symbolize_stacktrace = true;
        google::SetStderrLogging(google::FATAL);
        google::SetLogDestination(google::GLOG_INFO, "./Log/Infolog_");
        google::SetLogDestination(google::WARNING, "./Log/Warnlog_");
        google::SetLogDestination(google::ERROR, "./Log/Errorlog_");
        google::SetLogDestination(google::FATAL, "./Log/Fatallog_");
        FLAGS_minloglevel = google::INFO;
        google::InstallFailureSignalHandler();
    }
    inline ~LogMQ()
    {
        google::ShutdownGoogleLogging();
    }
};