#include "stm32f1xx_hal.h"
#include "key-read.h"

uint8_t keys[4][4] = {
	{'1', '2', '3', '+'},
	{'4', '5', '6', '-'},
	{'7', '8', '9', 'x'},
	{'c', '0', 'e', '/'},
};
uint16_t row_pins[4] = {ROW1_PIN, ROW2_PIN, ROW3_PIN, ROW4_PIN};
uint16_t col_pins[4] = {COL1_PIN, COL2_PIN, COL3_PIN, COL4_PIN};
uint8_t readKeypad(void)
{
	uint8_t row, col;


	for (row = 0; row < 4; row++) {
        HAL_GPIO_WritePin(ROW_PORT, row_pins[row], GPIO_PIN_SET);

        for (col = 0; col < 4; col++) {
            if (HAL_GPIO_ReadPin(COL_PORT, col_pins[col]) == GPIO_PIN_SET) {
                while (HAL_GPIO_ReadPin(COL_PORT, col_pins[col]) == GPIO_PIN_SET);
                HAL_GPIO_WritePin(ROW_PORT, row_pins[row], GPIO_PIN_RESET);
                HAL_Delay(20);
                return keys[row][col];
            }
        }

        HAL_GPIO_WritePin(ROW_PORT, row_pins[row], GPIO_PIN_RESET);
    }
	
    return 'n';
}
