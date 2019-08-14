//
// Created by hkh on 19-5-27.
//

#ifndef FIRSTCLIONPRO_LOGSTREAM_H
#define FIRSTCLIONPRO_LOGSTREAM_H


#include <string>
#include <string.h>
#include <memory>
const int small_size_t=4000;
const int large_size_t=9;//4000*1000;

template <int MaxSIZE>
class InfoBuffer{//信息流容器
public:
    InfoBuffer():cur_ptr(data_){}
    ~InfoBuffer(){}
    void append(const char* buf,size_t len){
        if(availSize()>len){
            memcpy(cur_ptr,buf,len);
            cur_ptr+=len;
        }
    }
    int availSize()const{
        return static_cast<int>(end()-cur_ptr);
    }
    char* current(){return cur_ptr;}
    void add(size_t len){cur_ptr+=len;}
    void reset(){cur_ptr=data_;}
    void bzero(){
        memset(data_, ' ', sizeof data_);
    }
    const char* getData()const{
        return data_;
    }
    int getLength()const{return static_cast<int>(cur_ptr-data_);}

private:
    const char* end() const{return data_+sizeof data_;}
    char data_[MaxSIZE];
    char* cur_ptr;

};
/*
 * 重载数据流
 */
class LogStream {
public:
    typedef InfoBuffer< small_size_t > Buffer;

    LogStream& operator<<(bool v)
    {
        buffer_.append(v?"1":"0",1);
        return *this;
    }

    //Interger
    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);

    LogStream& operator<<(const void*);

    //Float
    LogStream& operator<<(float v)
    {
        *this << static_cast<double>(v);
        return *this;
    }
    LogStream& operator<<(double);
    LogStream& operator<<(long double);

    //Char
    LogStream& operator<<(char v)
    {
        buffer_.append(&v,1);
        return *this;
    }
    LogStream& operator<<(const char* str)
    {
        if(str) buffer_.append(str,strlen(str));
        else buffer_.append("[Null]",6);
        return *this;
    }
    LogStream&operator<<(unsigned char* str)
    {
        *this<<(reinterpret_cast<const char*>(str));
    }
    LogStream&operator<<(const std::string& v)
    {
        buffer_.append(v.c_str(),v.size());
        return *this;
    }


    void append(const char* data, int len){
        buffer_.append(data,len);
    }
    const Buffer& getBuffer()const{return buffer_;}
    void resetBuffer(){buffer_.reset();}

private:
    void staticCheck();
    Buffer buffer_;
    template <typename T>
    void formatInteger(T);
    static const int kMaxNumericSize=32;//32位-4字节
};

template <typename T>
size_t convert(char buf[],T value);//转换


#endif //FIRSTCLIONPRO_LOGSTREAM_H
