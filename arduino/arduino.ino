#include <Arduino.h>

#include <WiFi.h>
#include <esp_camera.h>

#include "config.hpp" // include before all local files

#include "camera.hpp"
#include "network.hpp"

// esp_err_t camera_init();
// esp_err_t camera_capture(camera_fb_t *fb);
// void wifi_connect();

void setup()
{
    delay(5000); // allow for hardware to boot up, serial monitor to be connected

    Serial.begin(115200);
    Serial.setDebugOutput(true);

    Serial.println("");
    Serial.println("");

    wifi_connect();

    // camera init
    esp_err_t camera_err = camera_init();
    if (camera_err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", camera_err);
        return;
    }
}

void loop()
{
    // capture a frame
    camera_fb_t *fb = NULL;
    esp_err_t frame_err = camera_capture(fb);
    if (frame_err != ESP_OK)
    {
        Serial.printf("Camera capture failed with error 0x%x", frame_err);
        return;
    }

    // upload the frame to the server
    esp_err_t upload_err = upload_file(fb->buf, fb->len, (char*)"file");
    if (upload_err != ESP_OK)
    {
        Serial.printf("Upload failed with error 0x%x", upload_err);
        return;
    }

    // loop for now
    while (1)
    {
        ;
    }

    // return the frame buffer
    esp_camera_fb_return(fb);

    // delay interval seconds
    delay(INTERVAL * 1000);
}
