// hello
#include <stdio.h>

void client_connect(char *ip, int port);
void client_send(void);
void server_connect(void);
void server_recv(void);

int main(int argc, char *argv[]) {
    if (argc > 1 && argc != 3) {
        fprintf(stderr, "not enough args!");
        return -1;
    }

    if (argc == 1) {
        server_connect();
        server_recv();
        return 0;
    }

    // TODO check valid IP
    char *ip = argv[1];
    int port;
    sscanf(argv[2], "%d", &port);

    client_connect(ip, port);
    client_send();

    return 0;
}
