/**
 ******************************************************************************
 * @file           : main_HSImeasurement.c
 * @author         : Karalina Breiva
 * @brief          : HSI measurements
 ******************************************************************************
 **/

#include <stdint.h>

#define RCC_BASE_ADDR			0x40021000UL
#define RCC_CFGR_REG_OFFSET		0x0CUL
#define RCC_CFGR_REG_ADDR		(RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define GPIOA_BASE_ADDR			0x48000000UL

int main(void)
{
	/* Configure the RCC_CFGR MCO1 bit fields to select HSI as clock source */
    uint32_t *pRccCfgrReg = (uint32_t*)(RCC_CFGR_REG_ADDR);
    /* Clear 21 and 22 bit positions */
    *pRccCfgrReg &= ~(0x3 << 21);
    /* Configure NCO1 prescaler */
    *pRccCfgrReg |= (1 << 25);
    *pRccCfgrReg |= (1 << 26);
    
    /* Configure PA8 to AF0 mode to behave as MCO1 signal */
    /* Enable the peripheral clock for GPIOA peripheral */
    uint32_t *pRCCAhb1Enr = (uint32_t*)(RCC_BASE_ADDR + 0x30);
    *pRCCAhb1Enr |= (1 << 0);
    /* Configure the mode of GPIOA pin 8 as alternate function mode */
    uint32_t *pGRIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
    *pGRIOAModeReg &= ~(0x3 << 16); /*clear*/
    *pGRIOAModeReg |= (0x2 << 16);	/*set*/
    /* Configure the alternation function register to set the mode 0 for PA8 */
    uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
    *pGPIOAAltFunHighReg &= ~(0xf << 0);
    		
	for(;;);
}
