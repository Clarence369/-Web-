//
// Created by hkh on 19-5-20.
//

#ifndef FIRSTCLIONPRO_TIMEHEAP_H
#define FIRSTCLIONPRO_TIMEHEAP_H

#include <iostream>
#include <netinet/in.h>
#include <time.h>
#include <iostream>
using namespace std;
//用小根堆实现定时任务

using std::exception;//异常
#define BUFFER_SIZE 64
class Timer;//定时器-单元

struct client_data//客户端数据
{
    sockaddr_in address;//
    int sockfd;
    char buf[BUFFER_SIZE];
    Timer *timer;
};
typedef void (*callbackFunc)(client_data*);
class Timer{
public:
    Timer(int delay){
        expire=(time(NULL)+delay);
    }
public:
    time_t expire;
    callbackFunc time_callback;//函数指针-定时器回调函数
    client_data* user_data;
};

//时间堆结构-节点为定时器
/*
 *     1
 *    / \
 *   2   3
 *
 */
class TimeHeap{
private:
    Timer **array;//堆数组
    int capacity; //堆数组容量
    int cur_size; //当前元素个数
public:
    //初始化构造函数
    TimeHeap(int cap) throw(std::exception):capacity(cap),cur_size(0)
    {
         array=new Timer*[capacity];//每个里面都放着定时器指针
         if(!array)
         {
             throw std::exception();
         }
         for(int i=0;i<capacity;i++)
         {
             array[i]=NULL;//空指针
         }
    }
    //转换构造函数
    TimeHeap(Timer** init_array,int size,int cap)throw(std::exception)
            :cur_size(size),capacity(cap){
        if(capacity<size)
        {
            throw std::exception();
        }
        array=new Timer*[capacity];
        if(!array)
        {
            throw std::exception();
        }
        for(int i=0;i<capacity;i++)
        {
            array[i]=NULL;
        }
        if(size!=0)
        {
            for(int i=0;i<size;i++)
            {
                array[i]=init_array[i];
            }
            for(int i=0;i<cur_size;i++)
            {
                percolate_down(i);//下沉第i个
            }
        }
    }
    //析构函数
    ~TimeHeap(){
        for(int i=0;i<cur_size;i++)
        {
            delete array[i];
        }
        delete[] array;
    }
//功能函数
public:
    void add_timer(int delay,callbackFunc pcb)throw(std::exception)
    {
        Timer *timer;
        if(delay!=0)
        {
            timer=new Timer(delay);
            timer->time_callback=pcb;
        }

        if(!timer)
        {
            return;
        }
        if(cur_size>=capacity)
        {
            resize();//扩容，增大一倍
        }
        int hole=cur_size++;//空位
        int parent=0;
        for(;hole>0;hole=parent)//上滤空节点
        {
            parent=(hole-1)/2;//找到父节点
            //比较
            if(array[parent]->expire <= timer->expire)
            {
                break;
            }
            array[hole]=array[parent];
        }
        array[hole]=timer;
    }

    void del_timer(Timer *timer)
    {
        if(!timer)
        {
            return;
        }
        timer->time_callback=NULL;//清空回调函数即可,延迟销毁
    }

    //获取小根
    Timer* top()const{
        //常函数
        if(empty())
        {
            return NULL;
        }
        return array[0];
    }

    void pop(){
        if( empty() )
        {
            return;
        }
        if( array[0] )
        {
            auto tmp=array[0];
            array[0]=NULL;
            delete tmp;
            array[0] = array[--cur_size];
            //array[cur_size]=NULL;
            percolate_down( 0 );
        }
    }


    bool empty()const{
        return cur_size==0;
    }

    //心搏函数 计时 核心函数
    void tick()
    {
        //通过最小根的时间间隔 设置定时器
        Timer* temp=array[0];
        time_t cur=time(NULL);//获取系统时间，单位为秒;
        while(!empty()){//工作线程
            if(!temp)
            {
                break;
            }
            if(temp->expire>cur)//时间还没到
            {
                break;
            }
            //时间到了 执行回调
            //调用回调函数
            if(array[0]->time_callback!=NULL)
            {
                array[0]->time_callback(array[0]->user_data);
            }
            pop();
            temp=array[0];
        }
    }

private:
    void percolate_down(int hole)//下滤操作
    {
        Timer* temp=array[hole];//先提出来
        int child=0;
        while(1)
        {
            child=hole*2+1;//左子
            if(child>=cur_size) //超过了
            {
                 break;
            }
            //如果存在右子
            if(child<cur_size-1)
            {
                if(array[child]->expire>array[child+1]->expire)
                {
                  //右子小则需要替换下沉对象
                    child++;
                }
            }
            if(array[child]->expire < temp->expire)
            {
                array[hole]=array[child];
                hole=child;
            }
            else
            {
                break;
            }
        }
        array[hole]=temp;//取回来
    }

    //扩容
    void resize() throw(std::exception)
    {
        Timer** temp=new Timer*[2*capacity];
        for(int i=0;i<2*capacity;i++)
        {
            temp[i]=NULL;
        }
        if(!temp)
        {
            throw std::exception();
        }
        capacity=2*capacity;
        for(int i=0;i<cur_size;i++)
        {
            temp[i]=array[i];
        }
        delete[] array;//删掉指针就行
        array=temp;
    }

};


#endif //FIRSTCLIONPRO_TIMEHEAP_H
