#ifndef WIFI_H
#define WIFI_H

#include <string.h>

#include <zephyr/net/wifi_mgmt.h>
#include <zephyr/logging/log.h>


void wifi_connect(const char * ssid, const char * psk);
void wifi_disconnect();

#endif