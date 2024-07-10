#ifndef KEYREAD_
#define KEYREAD_

#define ROW_PORT GPIOB
#define ROW1_PIN GPIO_PIN_3
#define ROW2_PIN GPIO_PIN_4
#define ROW3_PIN GPIO_PIN_5
#define ROW4_PIN GPIO_PIN_6

#define COL_PORT GPIOC
#define COL1_PIN GPIO_PIN_6
#define COL2_PIN GPIO_PIN_7
#define COL3_PIN GPIO_PIN_8
#define COL4_PIN GPIO_PIN_9

uint8_t readKeypad(void);

#endif
