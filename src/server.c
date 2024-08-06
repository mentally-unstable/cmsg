// hello
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int cfd;
int fd;

char *read_msg(void);

void server_connect(void) {
    // create socket
    const int fd = socket(PF_INET, SOCK_STREAM, 0);

    // bind to open port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr))) {
        perror("bind error:");
        return;
    }

    // read port
    socklen_t addr_len = sizeof(addr);
    getsockname(fd, (struct sockaddr*) &addr, &addr_len);
    printf("server is on port %d\n", (int) ntohs(addr.sin_port));

    if (listen(fd, 1)) {
        perror("listen error:");
        return;
    }

    // accept incoming connection
    struct sockaddr_storage caddr;
    socklen_t caddr_len = sizeof(caddr);
    cfd = accept(fd, (struct sockaddr*) &caddr, &caddr_len);

    close(fd);
}

// TODO return string
void server_recv(void) {
    // read from client with recv!
    char buf[1024];
    recv(cfd, buf, sizeof(buf), 0);

    // print without looking
    printf("client says:\n    %s\n", buf);
}

char *read_msg(void) {
    char *s = (char *) malloc(128);

    char c = 0;
    int i = 0;
    while (c != '\n' && read(STDIN_FILENO, &c, 1) == 1) {
        if (i == 128)
            break;

        s[i] = c;

        i++;
    }

    return s;
}

void client_connect(char *ip, int port) {
    fd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_port = htons((short) port);

    // connect to machine at specified port
    char addrstr[NI_MAXHOST + NI_MAXSERV + 1];
    snprintf(addrstr, sizeof(addrstr), "%s:%d", ip, port);

    // parse into address
    inet_pton(AF_INET, addrstr, &addr.sin_addr);

    // connect to server
    if (connect(fd, (struct sockaddr*) &addr, sizeof(addr))) {
        perror("connect error:");
        return;
    }
}

void client_send(void) {
    char *msg = read_msg();
    send(fd, msg, strlen(msg) + 1, 0);
}
