//
// Created by hkh on 19-5-24.
//

#ifndef FIRSTCLIONPRO_WEB_MAIN_H
#define FIRSTCLIONPRO_WEB_MAIN_H

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
//时间
#include <sys/timerfd.h>
#include <time.h>
#include <netinet/tcp.h>
//日志
//#include "../base/Logging.h"
//#include "../base/AsyncLogging.h"
//#define MAX_FD 65536

extern int addfd( int epollfd, int fd, bool one_shot );
extern int removefd( int epollfd, int fd );

extern void addsig( int sig, void( handler )(int), bool restart);
//{
//    struct sigaction sa;
//    memset( &sa, '\0', sizeof( sa ) );
//    sa.sa_handler = handler;
//    if( restart )
//    {
//        sa.sa_flags |= SA_RESTART;
//    }
//    sigfillset( &sa.sa_mask );
//    assert( sigaction( sig, &sa, NULL ) != -1 );
//}



void callback(client_data*){
    cout<<"callback"<<endl;
}
AsyncLogging* aaaa;
void run()
{
    aaaa->threadFunc();
}

void logtest()
{
    //char*a="\nabcdef";
    while(1) {
     sleep(1);
     LOG_INFO<<"abcdef\n";
        //aaaa->append(a, sizeof(a));
    }
}

void asyncOutput(const char* msg, int len)
{
    aaaa->append(msg, len);//将此方法引入
}

int web_main( )
{
    addsig( SIGPIPE, SIG_IGN );
    AsyncLogging logging_("abc",10);
    Logger::setoutput(asyncOutput);
    aaaa=&logging_;
    thread t(run);
    t.detach();

    const char* ip = "127.0.0.1";//ip地址
    int port = atoi( "8888" );//端口

    ThreadPool< http_conn >* pool = NULL;
    try
    {
        pool = new ThreadPool< http_conn >;
    }
    catch( ... )
    {
        return 1;
    }

    //http_conn* users = new http_conn[ MAX_FD ];
    //http_conn* Master_user = new http_conn;
    //assert( users );
    int user_count = 0;

    int listenfd = socket( PF_INET, SOCK_STREAM, 0 );
    pool->listenfd=listenfd;
    assert( listenfd >= 0 );
    struct linger tmp = { 1, 0 };
    setsockopt( listenfd, SOL_SOCKET, SO_LINGER, &tmp, sizeof( tmp ) );

    int ret = 0;
    struct sockaddr_in address;
    bzero( &address, sizeof( address ) );
    address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &address.sin_addr );
    address.sin_port = htons( port );

    //设置复用
    const int on=1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));



    ret = bind( listenfd, ( struct sockaddr* )&address, sizeof( address ) );
    if(ret >= 0) {
        assert(ret >= 0);
    }
    ret = listen( listenfd, 10 );
    assert( ret >= 0 );

    epoll_event events[ MAX_EVENT_NUMBER ];
    int epollfd = epoll_create1( EPOLL_CLOEXEC );
    assert( epollfd != -1 );
    addfd( epollfd, listenfd, false );

    //***********************************

    TimeHeap m_timerheap(1);//初始化为2个定时器
    m_timerheap.add_timer(2,callback);
    m_timerheap.add_timer(4,callback);


    struct itimerspec new_value;
    new_value.it_interval.tv_sec=0;//周期数
    new_value.it_value.tv_sec=1;//设置时间
    //new_value.it_value.tv_nsec=m_timerheap.top()->expire-time(NULL);//设置时间
    auto m_timefd=timerfd_create(CLOCK_REALTIME,TFD_NONBLOCK);
    timerfd_settime(m_timefd,0,&new_value,NULL);
    //addfd(epollfd,m_timefd,1);//读时间

//***********************************

    while( true )
    {
        int number = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1 );
        if ( ( number < 0 ) && ( errno != EINTR ) )
        {
            printf( "epoll failure\n" );
            break;
        }

        for ( int i = 0; i < number; i++ )
        {
            int sockfd = events[i].data.fd;

            if(sockfd==m_timefd)//定时器处理
            {
                uint64_t data;
                read(events[i].data.fd, &data, sizeof(uint64_t));
                cout<<"[时间到啦]***************"<<endl;
                m_timerheap.tick();
                if(m_timerheap.top()!=NULL) {
                    cout<<"[重新设置时间]"<<m_timerheap.top()->expire - time(NULL)<<endl;
                    new_value.it_value.tv_sec = m_timerheap.top()->expire - time(NULL);//设置时间
                    timerfd_settime(m_timefd,0,&new_value,NULL);
                    modfd(epollfd,m_timefd,1);
                }
                else{
                    new_value.it_value.tv_sec=0;
                }
            }
            else if( sockfd == listenfd )//连接
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address );
                int connfd=-1;
                //queue<int> connfds;
                while((connfd= accept( listenfd, ( struct sockaddr* )&client_address, &client_addrlength))>0 )
                {
                    if (http_conn::m_user_count >= MAX_FD) {
                        show_error(connfd, "Internal server busy");
                        break;
                        //continue;
                    }
                    int enable = 1;
                    setsockopt(connfd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable));//关闭nagle
                    //connfds.push(connfd);
                    pool->wakeup(connfd);
                }

            }
        }
    }

    /*总结：
     * 服-》shutdown(写）
     *      close()<- 客
     * 服-》close()
     */

    close( epollfd );
    close( listenfd );
    delete pool;
    return 0;
}
#endif //FIRSTCLIONPRO_WEB_MAIN_H
