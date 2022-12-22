#ifndef NETWORK_CPP
#define NETWORK_CPP

#include "network.hpp"

// create buf
uint8_t *buf;
size_t buf_len;

void wifi_connect()
{
    log_i("Connecting to %s", WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // TODO: handle too many failed attempts (how many?)
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        log_d(".");
    }

    log_i("WiFi connected");
    log_i("IP address: %s", WiFi.localIP());
}

int responsef(uint8_t *buffer, int len)
{
    log_i("response from server: %s\n", buffer);
    return 0;
}

int rdataf(uint8_t *buffer, int len)
{
    // feed len bytes from buffer to the upload

    log_i("reading %d bytes", len);

    int ret = 0;
    for (int i = 0; i < len; i++)
    {
        buffer[i] = buf[i];
        ret++;
    }

    // advance buf
    buf += len;

    return ret;
}

void progressf(int percent)
{
    log_i("upload progress: %d%%\n", percent);
}

esp_err_t upload_file(uint8_t *data, size_t len, char *fieldName)
{
    log_i("Uploading %d bytes to %s:%d:%s with field %s", len, UPLOAD_HOST, UPLOAD_PORT, UPLOAD_PATH, fieldName);

    // copy to buffer
    buf = data;
    buf_len = len;

    WiFiClient client;
    UDHttp udh;

    // client.connect(UPLOAD_HOST, UPLOAD_PORT);

    // if (!client.connected())
    // {
    //     log_e("Failed to connect to %s:%d", UPLOAD_HOST, UPLOAD_PORT);
    //     return ESP_FAIL;
    // }

    // client.print(String("POST ") + UPLOAD_PATH + " HTTP/1.1\r\n" +
    //              "Host: " + UPLOAD_HOST + ":" + UPLOAD_PORT + "\r\n" +
    //              "Connection: close\r\n\r\n");

    udh.upload(UPLOAD_URL, "camera.jpg", len, rdataf, progressf, responsef);

    // reset buf
    buf = NULL;
    buf_len = 0;

    log_i("upload complete: %uKB %u", (uint32_t)(len / 1024));

    return ESP_OK;
}

#endif
