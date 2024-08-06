// hello

static void client(int port);
static void server(void);

int main(int argc, char *argv[]) {
    if (argc > 1 && !strcmp(argv[1], "client")) {
        if (argc != 3) {
            fprintf(stderr, "not enough args!");
            return -1;
        }

        int port;
        sscanf(argv[2], "%d", &port);

        client(port);
    } else {
        server();
    }

    return 0;
}
