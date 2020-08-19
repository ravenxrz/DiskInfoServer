//
// Created by raven on 2020/8/19.
//
/**
 * 服务端程序
 * Socket管理
 */

#ifndef DISKINFOSERVER_SERVER_H
#define DISKINFOSERVER_SERVER_H
#include <cstdint>
#include <string>

#include "linux/nvme.h"

class Server {
public:
    // 初始化服务
    /**
     *
     * @param port
     * @param listen_num
     */
    void init(uint32_t port ,int listen_num = 5);
    
    // 循环接收客户端请求,会block当前线程
    void accept_loop();
    
private:

private:
    int server_fd,new_socket;
};


#endif //DISKINFOSERVER_SERVER_H
