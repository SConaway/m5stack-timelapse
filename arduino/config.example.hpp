#ifndef CONFIG_H
#define CONFIG_H

// define wifi info
#define WIFI_SSID "your wifi ssid"
#define WIFI_PASS "your wifi password"
#define UPLOAD_URL "http://192.168.0.3:3000/api/upload"

// define interval in seconds
// #define INTERVAL 60 // 1 minute
#define INTERVAL 60 * 5 // 5 minutes
// #define INTERVAL 60*10 // 10 minutes
// #define INTERVAL 60*15 // 15 minutes
// #define INTERVAL 60*30 // 30 minutes
// #define INTERVAL 60*60 // 1 hour
// #define INTERVAL 60*60*24 // 1 day

// ===================
// Select camera model
// ===================
// #define CAMERA_MODEL_WROVER_KIT // Has PSRAM
// #define CAMERA_MODEL_ESP_EYE // Has PSRAM
// #define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM
// #define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
// #define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
// #define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
                                      // #define CAMERA_MODEL_M5STACK_UNITCAM // No PSRAM
//  #define CAMERA_MODEL_AI_THINKER // Has PSRAM
// #define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
//  ** Espressif Internal Boards **
// #define CAMERA_MODEL_ESP32_CAM_BOARD
// #define CAMERA_MODEL_ESP32S2_CAM_BOARD
// #define CAMERA_MODEL_ESP32S3_CAM_LCD

#endif
