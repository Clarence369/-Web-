//
// Created by hkh on 19-5-27.
//

#include "LogStream.h"
#include <algorithm>
#include <string.h>
#include <limits>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>

const char digits[]="9876543210123456789";
const char* zero=digits+9;

template <typename T>
size_t convert(char buf[],T value)//整形->字符
{
    T i = value;
    char *p = buf;

    do
    {
        int lsd = static_cast<int>(i % 10);
        i /= 10;
        *p++ = zero[lsd];
    } while (i != 0);

    if (value < 0)
    {
        *p++ = '-';
    }
    *p = '\0';
    std::reverse(buf, p);//buf tou p尾,调换顺序

    return p - buf;//返回大小
}

template class InfoBuffer<small_size_t>;
template class InfoBuffer<large_size_t>;
template<typename T>
//浮点型-》整形
void LogStream::formatInteger(T v) {
    if(buffer_.availSize()>=kMaxNumericSize)
    {
        size_t  len=convert(buffer_.current(),v);
        buffer_.add(len);
    }
}

LogStream& LogStream::operator<<(short v) {
    *this<< static_cast<int>(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned short v)
{
    *this << static_cast<unsigned int>(v);
    return *this;
}

LogStream& LogStream::operator<<(int v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned int v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long long v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long long v)
{
    formatInteger(v);
    return *this;
}

//浮点型直接格式化
LogStream& LogStream::operator<<(double v)
{
    if(buffer_.availSize()>=kMaxNumericSize)
    {
        int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12g", v);
        buffer_.add(len);
    }
    return *this;
}

LogStream& LogStream::operator<<(long double v)
{
    if (buffer_.availSize() >= kMaxNumericSize)
    {
        int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12Lg", v);
        buffer_.add(len);
    }
    return *this;
}














