//
// Created by hkh on 19-7-27.
//

#ifndef WEBSERVER_MUTEXLOCK_H
#define WEBSERVER_MUTEXLOCK_H
#include <pthread.h>
class MutexLockNew
{
public:
    MutexLockNew()
    {
        pthread_mutex_init(&mutex, NULL);
    }
    ~MutexLockNew()
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }
    void lock()
    {
        pthread_mutex_lock(&mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_t *get()
    {
        return &mutex;
    }
private:
    pthread_mutex_t mutex;

// 友元类不受访问权限影响
private:
    friend class Condition;
};


class MutexLockGuardNew
{
public:
    explicit MutexLockGuardNew(MutexLockNew &_mutex):
            mutex(_mutex)
    {
        mutex.lock();
    }
    ~MutexLockGuardNew()
    {
        mutex.unlock();
    }
private:
    MutexLockNew &mutex;
};
#endif //WEBSERVER_MUTEXLOCK_H
