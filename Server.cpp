//
// Created by raven on 2020/8/19.
//

#include "Server.h"
#include "DiskInfoGetter.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>


void Server::init(uint32_t port, int listen_num)
{
    struct sockaddr_in server_addr{};
    int opt = 1;
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons( port );
    
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, listen_num) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void Server::accept_loop()
{
//    struct sockaddr_in
    struct sockaddr_in address{};
    
    while(1)
    {
        // accept new client connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&address))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
       
        // 获取smart信息
        DiskData *diskData = DiskInfoGetter::getDiskData("/dev/nvme0n1");
        show_smart_log(diskData->smart_log);
//        printf("get diskData\n");
    }

}

