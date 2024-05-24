#include "app.h"
#include "FreeRTOS.h"

extern osMessageQueueId_t ledQueueHandle;

void hardware_init(void){
    
}

void my_console_logger(ulog_level_t level, char *msg) {
    printf("[%s]: %s\r\n",
        ulog_level_name(level),
        msg);
}

int app(void){
    ULOG_INIT();
    ULOG_SUBSCRIBE(my_console_logger, ULOG_DEBUG_LEVEL);

    ULOG_INFO("ulog is start!");

    LedState led_state = led_blink;
    osMessageQueuePut(ledQueueHandle,&led_state,0,0);
    return 0;
}

#if defined (__CC_ARM)
int fputc(int ch, FILE *stream) {
    /* 堵塞判断串口是否发送完成 */
    while((USART1->ISR & 0X40) == 0);

    /* 串口发送完成，将该字符发送 */
    USART1->TDR = (uint8_t) ch;

    return ch;
}
#elif defined(__GNUC__)
int _write(int file, char *pBuffer, int size) {
    for (int i = 0; i < size; i++) {
        while ((USART1->SR & 0X40) == 0);  //等待上一次串口数据发送完成
        USART1->DR = (uint8_t) pBuffer[i]; //写DR,串口1将发送数据
    }
    return size;
}
#endif
