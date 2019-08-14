//
// Created by hkh on 19-5-29.
//

#ifndef FIRSTCLIONPRO_LOGGER_H
#define FIRSTCLIONPRO_LOGGER_H

#define LOG_INFO Logger().m_logstream

#include "LogStream.h"
#include <iostream>
using namespace std;
typedef void(*OutputFunc)(const char*,int);

class Logger {

public:
    ~Logger(){
        goutput(m_logstream.getBuffer().getData(),m_logstream.getBuffer().getLength());
    }
    static void setoutput(OutputFunc out)
    {
        goutput=out;
    }
    static OutputFunc goutput;
    LogStream m_logstream;
};



#endif //FIRSTCLIONPRO_LOGGER_H
