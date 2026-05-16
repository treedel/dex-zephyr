#ifndef TCP_H
#define TCP_H

#include <stdint.h>
#include <zephyr/net/socket.h>
#include <zephyr/logging/log.h>


int tcp_start_server(uint16_t port);
int tcp_accept_connection(int server);
int tcp_close_connection(int client);
int tcp_receive_data(int client, void* buffer, size_t buffer_length);
void tcp_send_data(int client, void* buffer, size_t buffer_length);

#endif