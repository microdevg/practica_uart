#include <stdio.h>
#include <string.h>
#include <driver/uart.h>
#include "freertos/FreeRTOS.h"

#define UART                (UART_NUM_2)
#define BAUDRATE            (115200)
#define PIN_TX              (18)
#define PIN_RX              (19)
#define LEN_BUFFER          (1024)
#define MSG                 ("routine uart \n")

#define USE_STRUCT  1

#ifdef USE_STRUCT

uart_config_t uart_cfg ={
    .baud_rate = BAUDRATE,
    .data_bits = UART_DATA_8_BITS,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1
};

#endif



void app_main(void)
{
   
#ifdef USE_STRUCT
    uart_param_config(UART,&uart_cfg);
    
#else
    uart_set_baudrate(UART,BAUDRATE);
    uart_set_word_length(UART,UART_DATA_8_BITS);
    uart_set_parity(UART,UART_PARITY_DISABLE);
    uart_set_hw_flow_ctrl(UART,UART_HW_FLOWCTRL_DISABLE,0);
    uart_set_pin(UART,PIN_TX,PIN_RX,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
    uart_driver_install(UART,LEN_BUFFER,LEN_BUFFER,0,NULL,ESP_INTR_FLAG_SHARED);
#endif

    while(1){


        uart_write_bytes(UART,MSG,strlen(MSG));
        vTaskDelay(500/portTICK_PERIOD_MS);
        printf(MSG);
        
    }


}