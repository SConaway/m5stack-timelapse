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

    log_d("reading %d bytes", len);

    // check if we have enough data
    if (buf_len <= 0)
    {
        log_d("no more data to read");
        return 0;
    }

    // prevent reading more than we have
    if (len > buf_len)
    {
        len = buf_len;
        log_d("only reading %d", len);
    }

    int ret = 0;
    for (int i = 0; i < len; i++)
    {
        buffer[i] = buf[i];
        // printf("%c", buf[i]);
        ret++;
    }

    // advance buf
    buf += ret;
    buf_len -= ret;

    return ret;
}

void progressf(int percent)
{
    log_d("upload progress: %d%%\n", percent);
}

esp_err_t upload_file(uint8_t *data, size_t len)
{
    log_i("Uploading %d bytes to %s", len, UPLOAD_URL);

    // copy to buffer
    buf = data;
    buf_len = len;

    WiFiClient client;
    UDHttp udh;

    udh.upload(UPLOAD_URL, "camera.jpg", buf_len, rdataf, progressf, responsef);
    // `rdataf` will be called to read data from the buffer
    // `progressf` will be called to show upload progress
    // `responsef` will be called to show the response from the server
    //     (but this never seems to happen)

    // reset buf
    buf = NULL;
    buf_len = 0;

    log_i("upload complete: %uKB", (uint32_t)(len / 1024));

    return ESP_OK;
}

#endif
