#include <stdio.h>
#include <string.h>
#include "esp_camera.h"
#include "esp_log.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "driver/sdmmc_defs.h"
#include "driver/sdmmc_types.h"
#include "esp_vfs_fat.h"

// Camera configurations
#define CAMERA_MODEL_AI_THINKER
#define CAMERA_PIN_PWDN     -1
#define CAMERA_PIN_RESET    -1
#define CAMERA_PIN_XCLK     4
#define CAMERA_PIN_SIOD     18
#define CAMERA_PIN_SIOC     23
#define CAMERA_PIN_D7       36
#define CAMERA_PIN_D6       37
#define CAMERA_PIN_D5       38
#define CAMERA_PIN_D4       39
#define CAMERA_PIN_D3       35
#define CAMERA_PIN_D2       34
#define CAMERA_PIN_D1       32
#define CAMERA_PIN_D0       33
#define CAMERA_PIN_VSYNC    22
#define CAMERA_PIN_HREF     26
#define CAMERA_PIN_PCLK     21

// SD card configurations
#define SD_CARD_INTR_GPIO  34
#define SD_CARD_PIN_NUM_MISO 19
#define SD_CARD_PIN_NUM_MOSI 23
#define SD_CARD_PIN_NUM_CLK  18
#define SD_CARD_PIN_NUM_CS   5

static const char *TAG = "esp32-cam";

void initialize_sd_card()
{
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5
    };

    sdmmc_card_t *card;
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount SD card. Error: %s", esp_err_to_name(ret));
        return;
    }

    sdmmc_card_print_info(stdout, card);
}

void capture_photo()
{
    camera_config_t config = {
        .pin_pwdn = CAMERA_PIN_PWDN,
        .pin_reset = CAMERA_PIN_RESET,
        .pin_xclk = CAMERA_PIN_XCLK,
        .pin_sscb_sda = CAMERA_PIN_SIOD,
        .pin_sscb_scl = CAMERA_PIN_SIOC,
        .pin_d7 = CAMERA_PIN_D7,
        .pin_d6 = CAMERA_PIN_D6,
        .pin_d5 = CAMERA_PIN_D5,
        .pin_d4 = CAMERA_PIN_D4,
        .pin_d3 = CAMERA_PIN_D3,
        .pin_d2 = CAMERA_PIN_D2,
        .pin_d1 = CAMERA_PIN_D1,
        .pin_d0 = CAMERA_PIN_D0,
        .pin_vsync = CAMERA_PIN_VSYNC,
        .pin_href = CAMERA_PIN_HREF,
        .pin_pclk = CAMERA_PIN_PCLK,

        .xclk_freq_hz = 20000000,
        .ledc_timer = LEDC_TIMER_0,
        .ledc_channel = LEDC_CHANNEL_0,

        .pixel_format = PIXFORMAT_JPEG,
        .frame_size = FRAMESIZE_VGA,
        .jpeg_quality = 10,
        .fb_count = 2
    };

    // Initialize the camera
    esp_err_t ret = esp_camera_init(&config);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize camera. Error: %s", esp_err_to_name(ret));
        return;
    }

    // Capture image
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Failed to capture image");
        return;
    }

    // Save image to SD card
    char filename[32];
    snprintf(filename, sizeof(filename), "/sdcard/image.jpg");

    FILE *file = fopen(filename, "w");
    if (!file) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        esp_camera_fb_return(fb);
        return;
    }

    size_t bytes_written = fwrite(fb->buf, 1, fb->len, file);
    fclose(file);

    // Release the frame buffer
    esp_camera_fb_return(fb);

    if (bytes_written == 0) {
        ESP_LOGE(TAG, "Failed to write image data to file");
        return;
    }

    ESP_LOGI(TAG, "Image saved to file: %s", filename);
}

void app_main()
{
    initialize_sd_card();

    capture_photo();
}
