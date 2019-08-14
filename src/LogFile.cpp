//
// Created by hkh on 19-5-27.
//

#include "LogFile.h"
LogFile::LogFile(const std::string basename, int flushEveryN)
    :basename_(basename),
     flushEveryN_(flushEveryN),
     count_(0)
{
    //写出缓冲区
    fp_=fopen((basename+".log").c_str(), "aw");//创建 打开文件夹
    setbuffer(fp_,buffer_, sizeof(buffer_));//设置缓冲区
}

LogFile::~LogFile() {
    fclose(fp_);
}

void LogFile::append(const char *logline, int len) {
    std::lock_guard<std::mutex> lock(mutex_);
    append_unlocked(logline,len);
}

void LogFile::flush() {
    std::lock_guard<std::mutex> lock(mutex_);
    fflush(fp_);
}

void LogFile::append_unlocked(const char *logline, int len) {
    append_to_file(logline,len);
    ++count_;
    if(count_>=flushEveryN_)
    {
        count_=0;
        fflush(fp_);
    }
}

void LogFile::append_to_file(const char* logline,const size_t len)
{
    size_t n=this->write(logline,len);
    size_t remain=len-n;
    while(remain>0)
    {
        size_t x=this->write(logline+n,remain);
        if(x==0)
        {
            int err=ferror(fp_);
            if(err)
                fprintf(stderr,"apennd_to_file:fail\n");
        }
        n+=x;
        remain=len-n;
    }
}

size_t LogFile::write(const char* logline,size_t len)
{
    return fwrite_unlocked(logline, 1, len, fp_);
}