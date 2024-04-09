/**
 ******************************************************************************
 * @file           : main_HSEmeasurement.c
 * @author         : Karalina Breiva
 * @brief          : HSE measurements
 ******************************************************************************
 **/

#include <stdint.h>

#define RCC_BASE_ADDR			0x40021000UL
#define RCC_CFGR_REG_OFFSET		0x0CUL
#define	RCC_CR_REG_OFFSET		0x00UL
#define RCC_CFGR_REG_ADDR		(RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define RCC_CR_REG_ADDR			(RCC_BASE_ADDR + RCC_CR_REG_OFFSET)
#define GPIOA_BASE_ADDR			0x48000000UL

int main(void)
{
	uint32_t *pRccCrReg = (uint32_t*)(RCC_CR_REG_ADDR);
    uint32_t *pRccCfgrReg = (uint32_t*)(RCC_CFGR_REG_ADDR);

    /* Enable the HSE clock using HSEON bit (RCC_CR) */
    *pRccCfgrReg |= (0 << 16);
    /* Wait until HSE clock from the external crystal stabilizes (if crystal is connected) */
    while (!(*pRccCrReg & (1 << 17)));
    /* Switch the system clock to HSE (RCC_CFGR) */
    *pRccCfgrReg |= (1 << 0);

    /* Do MCO1 settings */

	/* Configure the RCC_CFGR MCO1 bit fields to select HSE as clock source */
    /* Clear 21 and set 22 */
    *pRccCfgrReg |= (1 << 22);
    /* Configure NC01 prescaler */
    /* Divisor as 4 */
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
