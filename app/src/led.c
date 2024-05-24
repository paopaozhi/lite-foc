#include "app.h"
#include "ulog.h"

// LED
extern osMessageQueueId_t ledQueueHandle;
extern osTimerId_t ledTimerHandle;

void ledTask(void *arg) {
  osStatus_t ret;
  LedState led_state;
  while (1) {
    ret = osMessageQueueGet(ledQueueHandle, &led_state, 0, osWaitForever);
    if (ret == osOK) {
      switch (led_state) {
        case led_blink:
          ULOG_DEBUG("led blink!");
          osTimerStart(ledTimerHandle,500);
          break;
        case led_open:
          ULOG_DEBUG("led open!");
          HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
          break;
        case led_close:
          ULOG_DEBUG("led close!");
          HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
          break;
        default:
          ULOG_ERROR("error led state!");
          break;
      }
    }
  }
}

void LedCallback(void *argument) { HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); }
