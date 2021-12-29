/* 
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include "app_priv.h"
#include <core2forAWS.h>
#include "display.h"

void app_main()
{
    Core2ForAWS_Init();
    Core2ForAWS_Sk6812_SetSideColor(SK6812_SIDE_LEFT, 0x0f4d8f);
    Core2ForAWS_Sk6812_SetSideColor(SK6812_SIDE_RIGHT, 0x0f4d8f);
    Core2ForAWS_Sk6812_Show();
    display_init();
}
