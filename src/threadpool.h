//
// Created by hkh on 19-5-14.
//

#ifndef FIRSTCLIONPRO_THREADPOOL_H
#define FIRSTCLIONPRO_THREADPOOL_H
/*
 * 仿照Linux高性能服务器中15-3例子
 * 半同步半反应堆线程池实现
 */

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include "http_conn.h"
#include <queue>
#include <sys/eventfd.h>
#include <mutex>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

//#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"
#include "TimeHeap.h"
#include "AsyncLogging.h"
#include "Logger.h"
#include "MutexLock.h"
#include <atomic>
//时间
#include <sys/timerfd.h>
#include <time.h>
#define MAX_FD 100000//65536
#define MAX_EVENT_NUMBER 1600
#define EVENT_WAITTIME 10000
#define ThreadNum 4
#define MaxRequest 10000
//#include "web_main.h"
//extern void addsig( int sig, void( handler )(int), bool restart = true );
void addsig( int sig, void( handler )(int), bool restart = true )
{
    struct sigaction sa;
    memset( &sa, '\0', sizeof( sa ) );
    sa.sa_handler = handler;
    if( restart )
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset( &sa.sa_mask );
    assert( sigaction( sig, &sa, NULL ) != -1 );
}
extern int addfd( int epollfd, int fd, bool one_shot );
extern int removefd( int epollfd, int fd );
struct connfdStruct
{
    int connfd;
    struct sockaddr_in client_address;
};
template <typename T>
class ThreadPool;
struct threadArg{
    ThreadPool<http_conn>* pool;
    int lunliu;
};
void show_error( int connfd, const char* info )
{
    printf( "%s", info );
    send( connfd, info, strlen( info ), 0 );
    close( connfd );
}
template <typename T>
class ThreadPool{
public:
    /*
     * 线程数量，允许最大请求
     */
    ThreadPool(int thread_number=ThreadNum,int max_requests=MaxRequest);//4线程
    ~ThreadPool();

    //添加任务->队列
    bool appendToDeque(T* request);
    bool appendSock(int connfd,struct sockaddr_in client_address,int index);
    void wakeup(int connfd,struct sockaddr_in& client_address);
    void wakeup();
    void wakeup(int fd);
    void wakeup(queue<int>& fd);
    int listenfd=-1;
private:
    static void *worker(void *arg);//工作线程
    void run(int index_);//主线程运行功能
private:
    //epoll_event events[ 10000 ];//监听10000个事件
    //vector<int> epollfds;//
    int efds[ThreadNum];//事件fd
    http_conn* users;//= new http_conn[ MAX_FD ];
    int m_thread_number;//线程池中线程数
    int m_max_requests;//最大请求数
    pthread_t * m_threads;//描述线程池的数组
    std::list<T*> m_workqueue;//请求队列
    MutexLock m_queuelocker;//互斥锁
    sem m_queuestat;//
    bool m_stop;//是否结束线程
    int lunliu=0;
    //deque< connfdStruct > *sockQueue;
    //queue<  int > *sockFds;
    vector<int> sockFds[ThreadNum];
    //vector<queue<int>*> sockFds;
    //vector<std::atomic_flag> atomiclocks=vector<std::atomic_flag>(4,ATOMIC_FLAG_INIT);
    std::atomic_flag atomiclocks[ThreadNum]={ATOMIC_FLAG_INIT};
    mutex m[ThreadNum];
    //vector<int> Load=vector<int>(m_thread_number,0);
    //mutable vector<MutexLockNew> m;
    //vector<atomic<bool>> callingPendingFunctors_=vector<atomic<bool>>(m_thread_number);
    atomic<bool>* callingPendingFunctors_=new atomic<bool>[4];
    volatile bool callingPendingFunctors2_[ThreadNum]={false};
    int DHUP=0;
    atomic<int> minLoad;

};

template <typename T>
ThreadPool<T>::ThreadPool(int thread_number,int max_requests):
        m_thread_number(thread_number),m_max_requests(max_requests),
        m_stop(false),m_threads(NULL)//线程池初始化
{
    if((m_thread_number<=0)||(m_max_requests<=0))
    {
        throw std::exception();

    }
    m_threads=new pthread_t[m_thread_number];//初始化４个线程池
    if(!m_threads)//创建失败
    {
        throw std::exception();
    }
    //efds=vector<int>(m_thread_number,-1);
    for(int i=0;i<m_thread_number;i++)
    {
        if((efds[i]=eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC))< 0)//创建失败
        {
            cout<<"创建efd失败"<<endl;
        }//创建eventfd
                //cout<<"初始化efds:"<<efds[i]<<endl;
    }
    users = new http_conn[ m_thread_number ];
    //sockQueue=new deque< connfdStruct >[m_thread_number];
    //vector<queue<int>*> sockFds_;
//    for(int i=0;i<m_thread_number;i++)
//    {
//        queue<int> my_queue;
//        sockFds.push_back(&my_queue);
//    }

    //sockFds=new vector<vector<int>>(4,new vector<int>);
    for(int i=0;i<m_thread_number;i++)
    {
        //vector<int> tmp;
        //sockFds[->push_back(tmp);
        callingPendingFunctors_[i].store(false);
    }

    minLoad=0;
    for(int i=0;i<thread_number;i++)
    {
        struct threadArg arg;
        arg.lunliu=i;
        arg.pool=this;
        if(pthread_create(&m_threads[i],NULL,worker,&arg)!=0)//线程运行起来
        {
            delete [] m_threads;
            throw std::exception();
        }
        sleep(0.5);
        if (pthread_detach(m_threads[i]))//隔离
        {
            delete[] m_threads;
            throw std::exception();
        }
    }
}

template <typename T>
ThreadPool<T>::~ThreadPool() {
    delete [] m_threads;
    delete [] users;
//    delete [] sockQueue;
    for(int i=0;i<m_thread_number;i++)
    {
        //close(epollfds[i]);
        close(efds[i]);
    }
    m_stop=true;
    cout<<"DHUP:"<<DHUP<<endl;
}

template <typename T>
bool ThreadPool<T>::appendToDeque(T *request) {//添加进请求队列中
    //加锁操作，保证互斥
    m_queuelocker.lock();
    if(m_workqueue.size()>m_max_requests)
    {//满了
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();//通过信号量控制它
    return true;
}


template <typename T>
void* ThreadPool<T>::worker(void *arg) {
    struct threadArg* a=(struct threadArg*)arg;
    int index=a->lunliu;
    ThreadPool *pool =(ThreadPool *)(a->pool);
    pool->run(index);
    return pool;
}

template <typename T>
bool ThreadPool<T>::appendSock(int connfd,struct sockaddr_in client_address,int index){
    struct connfdStruct tmp;
    tmp.connfd=connfd;
    tmp.client_address=client_address;
//    sockQueue[index].push_back(tmp);

}

template <typename T>
void ThreadPool<T>::run(int index_)//线程运行函数
{
    addsig( SIGPIPE, SIG_IGN );
    /**********************************************************************/
//    const char* ip = "127.0.0.1";//ip地址
//    int port = atoi( "8888" );//端口
//
//    int user_count = 0;
//    listenfd = socket( PF_INET, SOCK_STREAM, 0 );
//    assert( listenfd >= 0 );
//    struct linger tmp = { 1, 0 };
//    setsockopt( listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof( tmp ) );
//
//    int ret = 0;
//    struct sockaddr_in address;
//    bzero( &address, sizeof( address ) );
//    address.sin_family = AF_INET;
//    inet_pton( AF_INET, ip, &address.sin_addr );
//    address.sin_port = htons( port );
//
//    //设置复用
//    const int on=1;
//    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
//
//    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
//    if(ret >= 0) {
//        cout<<"ret:"<<ret<<endl;
//        assert(ret >= 0);
//    }
//    ret = listen( listenfd, 10 );
//    assert( ret >= 0 );

    /**********************************************************************/
    int index=index_;
    cout<<"thread:"<<index<<" in run"<<endl;
    epoll_event events[MAX_EVENT_NUMBER];//自己的事件
    int epollfd=epoll_create1(EPOLL_CLOEXEC);
    assert(epollfd!=-1);
    users[index].m_epollfd=epollfd;//本线程的epollfd
    //addfd( epollfd, listenfd, false );
    addfd( users[index].m_epollfd, efds[index], true );

    while(!m_stop)//开启
    {
        int number=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,EVENT_WAITTIME);
        //cout<<"thread:"<<index<<"call_out"<<endl;

        if((number<0)&&(errno!=EINTR))
        {
            printf("epoll failure\n");
            break;
        }
        //cout<<"number"<<number<<endl;

//        {
//            lock_guard <mutex> lock(m[index]);
        //callingPendingFunctors_[index].store(true);//true;
        callingPendingFunctors2_[index]=true;
            for (int i = 0; i < number; i++) {
                int sockfd = events[i].data.fd;//读取监听到的fd
                users[index].m_sockfd = sockfd;

                //定时器
//            if(sockfd==m_timefd)//定时器处理
//            {
//                uint64_t data;
//                read(events[i].data.fd, &data, sizeof(uint64_t));
//                cout<<"[时间到啦]***************"<<endl;
//                m_timerheap.tick();
//                if(m_timerheap.top()!=NULL) {
//                    cout<<"[重新设置时间]"<<m_timerheap.top()->expire - time(NULL)<<endl;
//                    new_value.it_value.tv_sec = m_timerheap.top()->expire - time(NULL);//设置时间
//                    timerfd_settime(m_timefd,0,&new_value,NULL);
//                    modfd(epollfd,m_timefd,1);
//                }
//                else{
//                    new_value.it_value.tv_sec=0;
//                }
//            }


//                if( sockfd == listenfd )//连接
//                {
//                    //cout<<"wakeup_begin"<<endl;
//                    struct sockaddr_in client_address;
//                    socklen_t client_addrlength = sizeof( client_address );
//                    int connfd=-1;
//                    while((connfd= accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength))>0 )
//                    {
//
//                        if (http_conn::m_user_count >= MAX_FD) {
//                            close(connfd);
//                            show_error(connfd, "Internal server busy");
//                            continue;
//                        }
//                        else
//                            users[index].init( connfd );
//                            //pool->wakeup(connfd);
//                        //pool->wakeup(connfd,client_address);
//                        //close(connfd);
//                        //唤醒
//                    }
////                if (connfd < 0) {
////                    printf("errno____ is: %d\n", errno);
////                    continue;
////                }
//
//
//                    //cout<<"wakeup_end"<<endl;
//
//                }
//                else
                if (sockfd == efds[index]) {
                    uint64_t u;
                    int n = read(sockfd, &u, sizeof(uint64_t));
//                    if(n!=sizeof(uint64_t))
//                    {
//                        cout<<"读错误"<<endl;
                    //}
                    modfd(users[index].m_epollfd, efds[index], EPOLLIN);
                }
                else if (events[i].events & (EPOLLRDHUP))//可以从底层被动知道客户端正常关闭
                {
                    //DHUP++;
                    users[index].close_conn_r(1);
                    //cout<<"[EPOLLRDHUP]××××××××"<<endl;
                } else if (events[i].events & (EPOLLHUP)) {

                    users[index].close_conn_r(1);
                    //cout << "[EPOLLHUP]××××××××" << endl;
                } else if (events[i].events & (EPOLLERR)) {//主动读写，检测发现对方异常关闭，比如掉线，此时不会主动通知对方，需要自己主动发送东西检验

                    users[index].close_conn_r(1);
                    //users[sockfd].close_conn();
                    cout << "[EPOLLERR]××××××××" << endl;
                } else if (events[i].events & EPOLLIN) {
                    //cout << "读处理" << endl;

                    if (users[index].read())//读完直接处理，如果是0则说明对方shutdown了
                    {
                        users[index].process();//解析处理接收到的事件,然后修改出EPOLLOUT，触发它发送
                        //cout << "读__" << endl;
                        //pool->appendToDeque( users + sockfd );
                    } else//读到0字节
                    {
                        users[index].close_conn_r();
                        //cout<<"被动关闭"<<endl;
                        //users[sockfd].close_conn();
                        //cout<<"[读完关闭]××××××××"<<endl;
                        //LOG_INFO<<"read\n";
                    }

                } else if (events[i].events & EPOLLOUT)//服务端主动shutdown(写),可以避免closewait状态
                {
                    //cout << "写处理" << endl;

                    if (!users[index].write())//返回是否关闭，根据keeplive
                    {
                        users[index].close_conn();//主动关闭
                        //cout<<"主动关闭"<<endl;
                        //LOG_INFO<<"writ\n";
                        //cout<<"[写完关闭]××××××××"<<endl;
                    }
                }
        }
        callingPendingFunctors2_[index]=false;
        //callingPendingFunctors_[index].store(false);//=false;
        vector<int> cur_socks;
        int size=0;
        {
            //lock_guard<mutex> lock(m[index]);
            while(atomiclocks[index].test_and_set());
            cur_socks.swap(sockFds[index]);//交换存储区
            atomiclocks[index].clear();
        }
            //printf("thread%d newsock_size:%d\n",index,size);
        for (int i = 0; i < cur_socks.size(); i++) {
            users[index].init(cur_socks[i]);//, NULL);//初始化，给epoll添加新的监督事件
        }
    }
}

template <typename T>
void ThreadPool<T>::wakeup(int connfd,struct sockaddr_in& client_address)
{
    lunliu++;
    int index=lunliu%m_thread_number;
    users[0].init(connfd);
}

template <typename T>
void ThreadPool<T>::wakeup()
{
    lunliu++;
    if(lunliu>=m_thread_number)  lunliu=0;
    uint64_t one = 1;
    ssize_t n = write(efds[lunliu], &one, sizeof one);//唤醒
}

template <typename T>
void ThreadPool<T>::wakeup(int fd)
{

//    while(1) {//谁开锁加在谁那
//        lunliu=(lunliu+1)%m_thread_number;
//        if (m[lunliu].try_lock())
//        {
//            //lock_guard<mutex> lock(m[lunliu]);
//            sockFds[lunliu].emplace_back(fd);
//            m[lunliu].unlock();
//            break;
//        }
//    }
    lunliu=(lunliu+1)%m_thread_number;
    {
        //lock_guard<mutex> lock(m[lunliu]);
        while(atomiclocks[lunliu].test_and_set());
        sockFds[lunliu].emplace_back(fd);
        atomiclocks[lunliu].clear();
    }

    if(callingPendingFunctors2_[lunliu]==false)
            //callingPendingFunctors_[lunliu].load(std::memory_order_acquire)==false)//不在循环中时要唤醒
    {
        uint64_t one = 1;
        ssize_t n = write(efds[lunliu], &one, sizeof one);//唤醒
    }
}

#endif //FIRSTCLIONPRO_THREADPOOL_H
