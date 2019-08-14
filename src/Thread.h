//
// Created by hkh on 19-5-28.
//

#ifndef FIRSTCLIONPRO_THREAD_H
#define FIRSTCLIONPRO_THREAD_H

#include <pthread.h>
#include <functional>
#include <unistd.h>
#include <thread>
//typedef void (*OutputFunc)(const char* msg, int len);
typedef void (*thread_fun)();
typedef std::function<void*(void*)> Functor;
class Thread{
public:
    Thread(){        std::thread a(func);
        a.detach();}

    Thread(thread_fun f);
//    Thread(thread_fun f){
//        func=f;
//    }
    //~Thread();
    void setoutput(thread_fun f)
    {
        func=f;
    }
    void start(){
        //func();
        std::thread a(func);
        a.detach();
    }
    pthread_t thread_id;
    thread_fun func;
    Functor funcfff;
//    OutputFunc a;
//    void asyncOutput(const char* msg, int len)
//    {
//        //cout<<msg<<endl;
//        //cout<<"abc"<<endl;
//    }
};
#endif //FIRSTCLIONPRO_THREAD_H
