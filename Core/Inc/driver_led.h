/*
 * driver_led.h
 *
 *  Created on: Apr 6, 2025
 *      Author: faiss
 */

#ifndef INC_DRIVER_LED_H_
#define INC_DRIVER_LED_H_

#include "main.h"

// Définitions des registres du MCP23S17
#define MCP23S17_ADDRESS  0x40  // Adresse SPI du MCP23S17 (A0, A1, A2 = GND)
#define MCP23S17_IOCON    0x0A  // Registre de configuration
#define MCP23S17_IODIRA   0x00  // Registre direction PORTA
#define MCP23S17_IODIRB   0x01  // Registre direction PORTB
#define MCP23S17_GPIOA    0x12  // Registre des données PORTA
#define MCP23S17_GPIOB    0x13  // Registre des données PORTB

void LED_Driver_Init(void);
void LED_SetGPIOA(uint8_t value);
void LED_SetGPIOB(uint8_t value);
void LED_SetPin(uint8_t pinNumber, GPIO_PinState state); // 0->7 : A0->A7, 8->15 : B0->B7
void chenillard(void);
void chennilard_unport(void);

#endif /* INC_DRIVER_LED_H_ */
