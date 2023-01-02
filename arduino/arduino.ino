#include <Arduino.h>

// #include <WiFi.h>
// #include <esp_camera.h>

#include "config.hpp" // include before all local files

#include "camera.hpp"
#include "network.hpp"

#include "esp_heap_caps.h"

// esp_err_t camera_init();
// esp_err_t camera_capture(camera_fb_t *fb);
// void wifi_connect();

void heap_caps_alloc_failed_hook(size_t requested_size, uint32_t caps, const char *function_name)
{
    log_e("%s was called but failed to allocate %d bytes with 0x%X capabilities. \n", function_name, requested_size, caps);
}

void blink(int ms)
{
    int blinks = ms / 100 / 2; // 100ms on, 100ms off
    for (int i = 0; i < blinks; i++)
    {
#ifdef LED_Pin
        digitalWrite(LED_Pin, HIGH);
#endif
        delay(100);
#ifdef LED_Pin
        digitalWrite(LED_Pin, LOW);
#endif
        delay(100);
    }
}

void setup()
{
#ifdef LED_Pin
    pinMode(LED_Pin, OUTPUT);
    digitalWrite(LED_Pin, HIGH);
#endif
    // set up heap alloc failed hook
    heap_caps_register_failed_alloc_callback(heap_caps_alloc_failed_hook);
    delay(5000); // allow for hardware to boot up, serial monitor to be connected

    Serial.begin(115200);
    Serial.setDebugOutput(true);

    log_i("Good morning!");

    // camera init
    esp_err_t camera_err = camera_init();
    if (camera_err != ESP_OK)
    {
        log_e("Camera init failed with error 0x%x, restarting soon", camera_err);
        blink(10 * 1000);
        ESP.restart();
    }

    wifi_connect();

#ifdef LED_Pin
    digitalWrite(LED_Pin, LOW);
#endif

    // waste 10 frames to let things settle
    for (int i = 0; i < 10; i++)
    {
        log_d("wasting frame");
        camera_fb_t *fb = esp_camera_fb_get();
        esp_camera_fb_return(fb);
        delay(500);
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
        blink(1 * 1000);
        ESP.restart();
    }

    camera_fb_t *fb = NULL;

    // waste a frame again
    esp_err_t frame_err = camera_capture(&fb);
    if (frame_err != ESP_OK || !fb->len)
    {
        log_e("Camera capture failed with error 0x%x, restarting\n", frame_err);
        blink(1 * 1000);
        ESP.restart();
        return;
    }
    // free it
    esp_camera_fb_return(fb);

    // capture a frame
    frame_err = camera_capture(&fb);
    if (frame_err != ESP_OK || !fb->len)
    {
        log_e("Camera capture failed with error 0x%x, restarting\n", frame_err);
        blink(1 * 1000);
        ESP.restart();
        return;
    }
    else
    {
        log_i("Frame Captured, width: %d, height: %d, size: %d", fb->width, fb->height, fb->len);
    }

    // upload the frame to the server
    esp_err_t upload_err = upload_file(fb->buf, fb->len, "camera.jpg");
    if (upload_err != ESP_OK)
    {
        log_e("Upload failed with error 0x%x", upload_err);
        blink(1 * 1000);
        ESP.restart();
        return;
    }

    // return the frame buffer
    esp_camera_fb_return(fb);

    // delay interval seconds
    delay(INTERVAL * 1000);
}
