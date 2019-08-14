cmake_minimum_required(VERSION 3.10)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(WebServer main.cpp
                src/threadpool.h
                src/http_conn.cpp
                src/http_conn.h
                src/web_main.h
                src/time_example.h
                src/Log.cpp
                src/Log.h
                src/LogStream.cpp
                src/LogStream.h
                src/AsyncLogging.cpp
                src/AsyncLogging.h
                src/LogFile.cpp
                src/LogFile.h
                src/Thread.h
                src/Thread.cpp
                src/Logger.cpp
                src/Logger.h src/MutexLock.h)
find_package(Threads REQUIRED)
target_link_libraries(WebServer Threads::Threads)