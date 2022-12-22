#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <Arduino.h>
#include <WiFi.h>
// #include <HTTPClient.h>
#include <UDHttp.h>

#include "config.hpp"

void wifi_connect();

// may need to cast to (char *) if using a string literal/constant
esp_err_t upload_file(uint8_t *data, size_t len, char *fieldName);

#endif
