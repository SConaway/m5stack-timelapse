#ifndef NETWORK_CPP
#define NETWORK_CPP

#include "network.hpp"

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

esp_err_t upload_file(uint8_t *data, size_t len, char *fieldName)
{
    log_i("Uploading %d bytes to %s with field %s", len, SERVER_URL, fieldName);

    WiFiClient client;
    HTTPClient http;

    if (!http.begin(client, UPLOAD_URL))
    {
        log_e("Failed to connect to server");
        return ESP_FAIL;
    }

    String boundary = "--------------------------" + String(random(0xFFFFFFFF), HEX);

    http.addHeader("Content-Length", String(len));
    http.addHeader("Content-Type", "multipart/form-data; boundary=" + boundary);

    int httpCode = http.POST("data"); //, len, fieldName);
    String body = http.getString();

    if (httpCode < 0)
    {
        log_e("Failed to upload file, error: %s, body: %s", http.errorToString(httpCode).c_str(), body);
        return ESP_FAIL;
    }

    log_i("Upload successful, response code: %d, body: %s", httpCode, body);

    http.end();

    return ESP_OK;
}

#endif
