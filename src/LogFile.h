//
// Created by hkh on 19-5-27.
//

#ifndef FIRSTCLIONPRO_LOGFILE_H
#define FIRSTCLIONPRO_LOGFILE_H

#include <string>
#include <memory>
#include "locker.h"
#include <mutex>
//负责写入文件和文件管理
class LogFile {
public:
    LogFile(const std::string basename,int flushEveryN=1024);
    ~LogFile();
    void append(const char* logline,int len);
    void flush();

private:
    void append_unlocked(const char* logline,int len);

    const std::string basename_;
    const int flushEveryN_;

    int count_;//
    std::mutex mutex_;

    /*
     * 文件管理区
     */
    FILE* fp_;
    char buffer_[64*1024];
    size_t write(const char* logline,size_t len);
    void append_to_file(const char* logline,const size_t len);
};

#endif //FIRSTCLIONPRO_LOGFILE_H
