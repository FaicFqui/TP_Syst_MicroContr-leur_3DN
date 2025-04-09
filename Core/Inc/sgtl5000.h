/*
 * sgtl5000.h
 *
 *  Created on: Apr 9, 2025
 *      Author: faiss
 */

#ifndef INC_SGTL5000_H_
#define INC_SGTL5000_H_

#include "main.h"
#include <stdint.h>

// I2C address (7 bits << 1 pour HAL)
#define SGTL5000_I2C_ADDR  (0x0A << 1)

// Register addresses
#define CHIP_DIG_POWER          0x0002
#define CHIP_CLK_CTRL           0x0004
#define CHIP_I2S_CTRL           0x0006
#define CHIP_SSS_CTRL           0x000A
#define CHIP_ADCDAC_CTRL        0x000E
#define CHIP_DAC_VOL            0x0010
#define CHIP_PAD_STRENGTH       0x0014
#define CHIP_ANA_ADC_CTRL       0x0020
#define CHIP_LINREG_CTRL        0x0022
#define CHIP_REF_CTRL           0x0026
#define CHIP_LINE_OUT_CTRL      0x0028
#define CHIP_LINE_OUT_VOL       0x002C
#define CHIP_SHORT_CTRL         0x002E
#define CHIP_ANA_CTRL           0x0030
#define CHIP_ANA_POWER          0x0034


extern I2C_HandleTypeDef *sgtl5000_i2c;

// Function publiques
void SGTL5000_Init(void);
void SGTL5000_WriteRegister(uint16_t reg, uint16_t val);
uint16_t SGTL5000_ReadRegister(uint16_t reg);


#endif
