#include <Arduino.h>

// #include <WiFi.h>
// #include <esp_camera.h>

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

    log_i("Good morning!");

    wifi_connect();

    // camera init
    esp_err_t camera_err = camera_init();
    if (camera_err != ESP_OK)
    {
        log_e("Camera init failed with error 0x%x, restarting soon", camera_err);
        delay(10 * 1000);
        ESP.restart();
    }

    log_i("at your service");
}
void loop()
{

    // check if connected to WiFi
    // if not, restart
    if (WiFi.status() != WL_CONNECTED)
    {
        log_e("WiFi disconnected, restarting");
        ESP.restart();
    }

    // capture a frame
    camera_fb_t *fb = NULL;
    esp_err_t frame_err = camera_capture(&fb);
    if (frame_err != ESP_OK || !fb->len)
    {
        log_e("Camera capture failed with error 0x%x\n", frame_err);
        return;
    }
    else
    {
        log_i("Frame Captured, width: %d, height: %d, size: %d", fb->width, fb->height, fb->len);
    }

    // upload the frame to the server
    esp_err_t upload_err = upload_file(fb->buf, fb->len);
    if (upload_err != ESP_OK)
    {
        log_e("Upload failed with error 0x%x", upload_err);
        return;
    }

    // return the frame buffer
    esp_camera_fb_return(fb);

    // delay interval seconds
    delay(INTERVAL * 1000);
}
