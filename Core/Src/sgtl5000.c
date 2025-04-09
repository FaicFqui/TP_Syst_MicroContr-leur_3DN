/*
 * sglt5000.c
 *
 *  Created on: Apr 9, 2025
 *      Author: faiss
 */


#include "sgtl5000.h"

I2C_HandleTypeDef *sgtl5000_i2c = NULL;

void SGTL5000_WriteRegister(uint16_t reg, uint16_t val)
{
    uint8_t data[4];
    data[0] = (reg >> 8) & 0xFF;
    data[1] = reg & 0xFF;
    data[2] = (val >> 8) & 0xFF;
    data[3] = val & 0xFF;

    HAL_I2C_Master_Transmit(sgtl5000_i2c, SGTL5000_I2C_ADDR, data, 4, HAL_MAX_DELAY);
}

uint16_t SGTL5000_ReadRegister(uint16_t reg)
{
    uint8_t addr[2];
    uint8_t rx[2];

    addr[0] = (reg >> 8) & 0xFF;
    addr[1] = reg & 0xFF;

    HAL_I2C_Master_Transmit(sgtl5000_i2c, SGTL5000_I2C_ADDR, addr, 2, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(sgtl5000_i2c, SGTL5000_I2C_ADDR, rx, 2, HAL_MAX_DELAY);

    return ((uint16_t)rx[0] << 8) | rx[1];
}

void SGTL5000_Init(void)
{
    HAL_Delay(50); // temsp de stabilisation apres sous tension

    // Configuration SGTL5000
    SGTL5000_WriteRegister(CHIP_ANA_POWER,       0x7260);  // Allume MIC, LINE_IN, LINE_OUT, VAG, ADC, DAC
    SGTL5000_WriteRegister(CHIP_LINREG_CTRL,     0x006C);  // Active LDO
    SGTL5000_WriteRegister(CHIP_REF_CTRL,        0x01F2);  // Contrôle tension VAG
    SGTL5000_WriteRegister(CHIP_LINE_OUT_CTRL,   0x032F);  // Impédance de sortie ligne
    SGTL5000_WriteRegister(CHIP_LINE_OUT_VOL,    0x1F1F);  // Volume sortie ligne
    SGTL5000_WriteRegister(CHIP_SHORT_CTRL,      0x4446);  // Protection court-circuit
    SGTL5000_WriteRegister(CHIP_ANA_CTRL,        0x0137);  // Active l’entrée LINE_IN
    SGTL5000_WriteRegister(CHIP_DIG_POWER,       0x0073);  // Active I2S, DAC, ADC, DAP
    SGTL5000_WriteRegister(CHIP_CLK_CTRL,        0x0004);  // MCLK / 256 = 48kHz
    SGTL5000_WriteRegister(CHIP_I2S_CTRL,        0x0130);  // I2S, 16 bits, maître ou esclave selon config
    SGTL5000_WriteRegister(CHIP_SSS_CTRL,        0x0010);  // ADC → I2S_OUT & I2S_IN → DAC
    SGTL5000_WriteRegister(CHIP_ADCDAC_CTRL,     0x0000);  // Pas de mute
    SGTL5000_WriteRegister(CHIP_DAC_VOL,         0x3C3C);  // Volume DAC
    SGTL5000_WriteRegister(CHIP_PAD_STRENGTH,    0x015F);  // Force I/O



    HAL_Delay(10); // temsp de stabilisation
}
