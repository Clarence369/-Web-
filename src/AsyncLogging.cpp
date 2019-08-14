//
// Created by hkh on 19-5-27.
//

#include "AsyncLogging.h"
#include <assert.h>
void abc()
{
    while(1) {
        std::cout << "abc" << std::endl;
        sleep(2);
    }
}
AsyncLogging::AsyncLogging(const std::string logFileName_, int flushInterval)
        :flushInterval_(flushInterval),
         basename_(logFileName_),
         currentBuffer_(new Buffer),
         nextBuffer_(new Buffer),
         running_(true)
{
    assert(logFileName_.size()>1);
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    buffers_.reserve(16);//分配16个
//    std::thread a(threadFunc);
//    a.detach();
    //启动线程
}

void AsyncLogging::append(const char* logline,int len)
{
    //pthread_cond_wait(&cond_,&mutex_);

    std::unique_lock <std::mutex> lck(mutex_);
    if(currentBuffer_->availSize()>len)
    {
        currentBuffer_->append(logline,len);
        //cout<<"写入"<<endl;
    }
    else
    {
        buffers_.push_back(currentBuffer_);
        currentBuffer_.reset();//初始化
        if(nextBuffer_)//存在
        {
            currentBuffer_=std::move(nextBuffer_);
        }
        else
        {
            currentBuffer_.reset(new Buffer);//产生一块新的
        }
        currentBuffer_->append(logline, len);
        cond_.notify_all();
        //pthread_cond_signal(&cond_);//唤醒
    }
}

void AsyncLogging::threadFunc() {
//    while(1)
//    {
//        std::cout<<"in thread"<<std::endl;
//        sleep(1);
//    }

    assert(running_==true);
    LogFile output(basename_);//文件
    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBuffer2(new Buffer);

    newBuffer1->bzero();
    newBuffer2->bzero();

    BufferVector buffersToWrite;
    buffersToWrite.reserve(16);

    while(running_)
    {
        assert(newBuffer1 && newBuffer1->getLength() == 0);
        assert(newBuffer2 && newBuffer2->getLength() == 0);
        assert(buffersToWrite.empty());

        {
            std::unique_lock <std::mutex> lck(mutex_);
            if (buffers_.empty())  // unusual usage!
            {
                cond_.wait_for(lck,std::chrono::seconds(3));//等待
            }
            buffers_.push_back(currentBuffer_);
            currentBuffer_.reset();

            currentBuffer_ = std::move(newBuffer1);
            buffersToWrite.swap(buffers_);
            if (!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);
            }
        }

        assert(!buffersToWrite.empty());

        if (buffersToWrite.size() > 25)
        {
            buffersToWrite.erase(buffersToWrite.begin()+2, buffersToWrite.end());
        }

        for (size_t i = 0; i < buffersToWrite.size(); ++i)
        {
            output.append(buffersToWrite[i]->getData(), buffersToWrite[i]->getLength());
        }

        if (buffersToWrite.size() > 2)
        {
            // drop non-bzero-ed buffers, avoid trashing
            buffersToWrite.resize(2);
        }

        if (!newBuffer1)
        {
            assert(!buffersToWrite.empty());
            newBuffer1 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }

        if (!newBuffer2)
        {
            assert(!buffersToWrite.empty());
            newBuffer2 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer2->reset();
        }

        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
//        assert(newBuffer1&&newBuffer1->getLength()==0);
//        assert(newBuffer2&& newBuffer2->getLength()==0);
//        assert(buffersToWrite.empty());//空
//        {//缓存交换区
//            std::unique_lock <std::mutex> lck(mutex_);
//            //MutexLockGuard lock_(mutex_);
//            if(buffers_.empty())
//            {
//                cond_.wait(lck);
//                //pthread_cond_wait(&cond_,&mutex_.mutex_);
//            }
//            buffers_.push_back(currentBuffer_);
//            currentBuffer_.reset();
//
//            currentBuffer_=std::move(newBuffer1);
//            buffersToWrite.swap(buffers_);
//            if(!nextBuffer_)
//            {
//                nextBuffer_=std::move(newBuffer2);
//            }
//        }
//
//        assert(!buffersToWrite.empty());//飞空
//
//        if(buffersToWrite.size()>25)
//        {
//            buffersToWrite.erase(buffersToWrite.begin()+2,buffersToWrite.end());
//        }
//
//        for(size_t i=0;i<buffersToWrite.size();++i){
//            output.append(buffersToWrite[i]->getData(),buffersToWrite[i]->getLength());
//        }
//
//        if(buffersToWrite.size()>2)
//        {
//            buffersToWrite.resize(2);
//        }
//
//        if(!newBuffer1)
//        {
//            assert(!buffersToWrite.empty());
//            newBuffer1=buffersToWrite.back();
//            buffers_.pop_back();
//            newBuffer1->reset();
//        }
//
//        if (!newBuffer2)
//        {
//            assert(!buffersToWrite.empty());
//            newBuffer2 = buffersToWrite.back();
//            buffersToWrite.pop_back();
//            newBuffer2->reset();
//        }
//
//        buffersToWrite.clear();
//        output.flush();
//    }

}