#include "Server.h"


void server_start();

int main(int argc, char *argv[])
{
    server_start();
    return 0;
}


void server_start()
{
   Server server;
   server.init(4000,5);
   server.accept_loop();
}