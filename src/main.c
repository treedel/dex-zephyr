#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <wifi.h>
#include <wifi_info.h>
#include <tcp.h>
#include <string.h>

#include <dex_registry.h>


LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

#define BIND_PORT 4343

int server, client;


bool tcp_send_frame(void* buffer, size_t buffer_length) {
	tcp_send_data(client, buffer, buffer_length);
	return true;
}

int main(void) {
	printk("Attempting to connect to WiFi\n");
	wifi_connect(WIFI_SSID, WIFI_PSK);
	
	server = tcp_start_server(BIND_PORT);

	while (1) {
		client = tcp_accept_connection(server);
		if (client >= 0) {
			DexContext ctx;
			dex_initalize(&ctx, tcp_send_frame);
			
			uint8_t id;
			dex_register_topic(&ctx, "TopicA", DexMessageType_MSG_DAT_MOT, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));
			dex_register_topic(&ctx, "TopicB", DexMessageType_MSG_DAT_MOT, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));
			dex_register_topic(&ctx, "TopicC", DexMessageType_MSG_DAT_ENC, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));
			dex_register_topic(&ctx, "TopicD", DexMessageType_MSG_DAT_ENC, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));
			dex_register_topic(&ctx, "TopicE", DexMessageType_MSG_DAT_MOT, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));
			dex_register_topic(&ctx, "TopicF", DexMessageType_MSG_DAT_MOT, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));
			dex_register_topic(&ctx, "TopicG", DexMessageType_MSG_DAT_MOT, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));
			dex_register_topic(&ctx, "TopicH", DexMessageType_MSG_DAT_MOT, &id);
			printk("%d\n", id);
			k_sleep(K_MSEC(1000));

            tcp_close_connection(client);
        }
	}

	return 0;
}



/* #include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <wifi.h>
#include <wifi_info.h>
#include <tcp.h>
#include <string.h>


LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

int main(void) {
	printk("CPUs: %d\n", arch_num_cpus());
	printk("Attempting to connect to WiFi\n");
	wifi_connect(WIFI_SSID, WIFI_PSK);

	int server, client;
	
	server = start_server(BIND_PORT);

	while (1) {
		client = accept_connection(server);
		if (client >= 0) {
            
			while (1) {
				size_t buffer_length = 128;
				char buffer[buffer_length];

				int len = read_data(client, (void*) buffer, buffer_length);
				
				// For identifying data as string
				buffer[len++] = '\0';

				// Exit condition
				if (!strcmp(buffer, "/close\r\n")) {
					break;
				}

				printk("%s", buffer);

				// Acknowledgement
				send_data(client, (void*) "OK\n", 4);
			}

            close_connection(client);
        }
	}

	return 0;
}
 */