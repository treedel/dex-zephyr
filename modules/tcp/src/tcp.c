#include <tcp.h>


LOG_MODULE_REGISTER(tcp);

int tcp_start_server(uint16_t port) {
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = {
            .s_addr = htonl(INADDR_ANY),
        },
        .sin_port = htons(port),
    };

    int server;
    server = zsock_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server < 0) {
		LOG_ERR("Socket error");
		return 1;
	}

    zsock_bind(server, (struct sockaddr*) &addr, sizeof(addr));
    zsock_listen(server, 1);

    LOG_INF("TCP Server started");

    return server;
}

int tcp_accept_connection(int server) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char addr_str[32];

    int client = zsock_accept(server, (struct sockaddr *) &client_addr, &client_addr_len);
    zsock_inet_ntop(client_addr.sin_family, &client_addr.sin_addr, addr_str, sizeof(addr_str));
    LOG_INF("Connection from %s", addr_str);

    return client;
}

int tcp_close_connection(int client) {
    int ret = zsock_close(client);
    LOG_INF("Disconnected from client");
    return ret;
}

int tcp_receive_data(int client, void* buffer, size_t buffer_length) {
    int len = zsock_recv(client, buffer, buffer_length, 0);
    if (len < 0) {
        LOG_ERR("Error receiving data: %d", errno);
    }
    else if (len == 0) {
        LOG_INF("Connection closed");
    }
    return len;
}

void tcp_send_data(int client, void* buffer, size_t buffer_length) {
    char* p = buffer;
    int out_len;

    do {
        out_len = zsock_send(client, p, buffer_length, 0);
        if (out_len < 0) {
            LOG_ERR("Error sending data: %d", errno);
            continue;
        }
        p += out_len;
        buffer_length -= out_len;
    } while (buffer_length);
}