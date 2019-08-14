//
// Created by hkh on 19-5-25.
//

#ifndef FIRSTCLIONPRO_LOG_H
#define FIRSTCLIONPRO_LOG_H

#include <memory>
#include <fcntl.h>
#include "locker.h"
#include <vector>
using namespace std;
//#define MAX_BUFFER 1024
/*
 * 异步日志库
 * 功能包含：
 * TRACE:追踪
 * DEBUG：调试
 * INFO：信息
 * WARN：提醒
 * ERROR：错误
 * FATAL：
 * 级别划分
 * 前后端分离
 * 保证低开销和cpu占用率
 * 信息行：日期 	时间 	线程 	级别 	正文 	源文件名称 	行号
 */
class Log {

public:
    Log(char *path){
        //open()
    }
    ~Log();
public:
    void postWrite();//后端写出
    void foreRead();//前端读进
    void setLogLevel();
private:
    //unique_ptr<char> cur_buffer(20);
    //unique_ptr<char> next_buffer(20);
    //vector<unique_ptr<char>> read_buffer(MAX_BUFFER);

    char* new1_buffer[20];
    char* new2_buffer[20];
    //vector<unique_ptr<char>> write_buffer(MAX_BUFFER);//存放指针

    MutexLock m_locker;
};


#endif //FIRSTCLIONPRO_LOG_H
