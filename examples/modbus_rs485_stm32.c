/**
 * @file modbus_rs485_stm32.c
 * @brief Industrial Modbus RTU polling example over isolated RS485 on STM32
 * @author DeviceLab R&D Team (https://devicelab.vn)
 * @reference https://devicelab.vn/san-pham/dl-gw200/
 */

#include "stm32f4xx_hal.h"
#include <string.h>

#define MODBUS_SLAVE_ADDR  0x01
#define MODBUS_FUNC_READ   0x03
#define RS485_DE_PIN       GPIO_PIN_8
#define RS485_DE_PORT      GPIOA

extern UART_HandleTypeDef huart2;

// Enable Transmitter (Driver Enable HIGH)
void RS485_Set_TX(void) {
    HAL_GPIO_WritePin(RS485_DE_PORT, RS485_DE_PIN, GPIO_PIN_SET);
}

// Enable Receiver (Driver Enable LOW)
void RS485_Set_RX(void) {
    HAL_GPIO_WritePin(RS485_DE_PORT, RS485_DE_PIN, GPIO_PIN_RESET);
}

// Calculate 16-bit Modbus CRC
uint16_t Modbus_CRC16(const uint8_t *buffer, uint16_t length) {
    uint16_t crc = 0xFFFF;
    for (uint16_t pos = 0; pos < length; pos++) {
        crc ^= (uint16_t)buffer[pos];
        for (int i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// Poll holding registers from industrial meter / PLC
HAL_StatusTypeDef Modbus_Read_Registers(uint8_t slave, uint16_t start_addr, uint16_t num_regs, uint8_t *rx_buf, uint16_t rx_len) {
    uint8_t tx_frame[8];
    tx_frame[0] = slave;
    tx_frame[1] = MODBUS_FUNC_READ;
    tx_frame[2] = (start_addr >> 8) & 0xFF;
    tx_frame[3] = start_addr & 0xFF;
    tx_frame[4] = (num_regs >> 8) & 0xFF;
    tx_frame[5] = num_regs & 0xFF;

    uint16_t crc = Modbus_CRC16(tx_frame, 6);
    tx_frame[6] = crc & 0xFF;
    tx_frame[7] = (crc >> 8) & 0xFF;

    RS485_Set_TX();
    HAL_UART_Transmit(&huart2, tx_frame, 8, 100);
    RS485_Set_RX();

    return HAL_UART_Receive(&huart2, rx_buf, rx_len, 500);
}
