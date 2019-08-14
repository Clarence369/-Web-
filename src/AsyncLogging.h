//
// Created by hkh on 19-5-27.
//

#ifndef FIRSTCLIONPRO_ASYNCLOGGING_H
#define FIRSTCLIONPRO_ASYNCLOGGING_H

#include <string>
#include "LogStream.h"
#include <memory>
#include <vector>
#include "locker.h"
#include <thread>
#include "LogFile.h"
#include <iostream>
#include "Thread.h"
#include <thread>
#include <condition_variable>
class AsyncLogging {
public:
     AsyncLogging(const std::string basename, int flushInterval=2);
     ~AsyncLogging(){
     }
    void append(const char* logline,int len);
    void threadFunc();//最关键
private:

//    typedef InfoBuffer<large_size_t> Buffer;//大块内存
//    typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
//    typedef std::shared_ptr<Buffer> BufferPtr;
    typedef InfoBuffer<large_size_t> Buffer;
    typedef std::vector<std::shared_ptr<Buffer>> BufferVector;
    typedef std::shared_ptr<Buffer> BufferPtr;

    const int flushInterval_;
    bool running_;//判断是否运行
    std::string basename_;
    //pthread_mutex_t mutex_;
    mutex mutex_;
    //unique_ptr<thread> thread_;
    //Thread m_thread;
    //unique_ptr<thread> thread_;

    condition_variable cond_;
    //pthread_cond_t cond_;
    BufferPtr currentBuffer_;
    BufferPtr nextBuffer_;
    BufferVector buffers_;
};


#endif //FIRSTCLIONPRO_ASYNCLOGGING_H
