#include<stddef.h>
#include<stdint.h>

#define __vo volatile
#define __weak __attribute__((weak))

#define FLASH_BASEADDR						0x08000000U
#define SRAM_BASEADDR						0x20000000U
#define ROM_BASEADDR						0x1FFF0000U  //System memory from which the device boots in System memory boot mode


/*
 * AHBx and APBx Bus Peripheral base addresses
 */


#define APB1PERIPH_BASEADDR						0x40000000U
#define APB2PERIPH_BASEADDR						0x40010000U
#define AHB1PERIPH_BASEADDR						0x40020000U
#define AHB2PERIPH_BASEADDR						0x50000000U

#define GPIOD_BASEADDR 					 (AHB1PERIPH_BASEADDR + 0x0C00)
#define SYSCFG_BASEADDR        				(APB2PERIPH_BASEADDR + 0x3800)
#define EXTI_BASEADDR						(APB2PERIPH_BASEADDR + 0x3C00)
#define RCC_BASEADDR                                          (AHB1PERIPH_BASEADDR+ 0X3800)

/*
 * IRQ(Interrupt Request) Numbers of STM32F407x MCU
 * NOTE: update these macros with valid values according to your MCU
 * TODO: You may complete this list for other peripherals
 */

#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7


//some generic macros

#define ENABLE 				1
#define DISABLE 			0
#define SET 				ENABLE
#define RESET 				DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET
#define FLAG_RESET         RESET
#define FLAG_SET 			SET



typedef struct
{
	__vo uint32_t MODER;                        /*!< GPIO port mode register,                    	Address offset: 0x00      */
	__vo uint32_t OTYPER;                       /*  										Address offset: 0x04      */
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];					 /*!< AFR[0] : GPIO alternate function low register, AF[1] : GPIO alternate function high register    		Address offset: 0x20-0x24 */
}GPIO_RegDef_t;
typedef struct
{
  __vo uint32_t CR;            /*  										Address offset: 0x00 */
  __vo uint32_t PLLCFGR;       /*  										Address offset: 0x04 */
  __vo uint32_t CFGR;          /*  										Address offset: 0x08 */
  __vo uint32_t CIR;           /*  										Address offset: 0x0C */
  __vo uint32_t AHB1RSTR;      /*  										Address offset: 0x10 */
  __vo uint32_t AHB2RSTR;      /*  										Address offset: 0x14 */
  __vo uint32_t AHB3RSTR;      /*  										Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                       */
  __vo uint32_t APB1RSTR;      /*  										Address offset: 0x20 */
  __vo uint32_t APB2RSTR;      /*  										Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                  */
  __vo uint32_t AHB1ENR;       /*  										Address offset: 0x30 */
  __vo uint32_t AHB2ENR;       /*  										Address offset: 0x34 */
  __vo uint32_t AHB3ENR;       /*  										Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                       */
  __vo uint32_t APB1ENR;       /*  										Address offset: 0x40 */
  __vo uint32_t APB2ENR;       /*  										Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                  */
  __vo uint32_t AHB1LPENR;     /*  										Address offset: 0x50 */
  __vo uint32_t AHB2LPENR;     /*  										Address offset: 0x54 */
  __vo uint32_t AHB3LPENR;     /*  										Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                       */
  __vo uint32_t APB1LPENR;     /*  										Address offset: 0x60 */
  __vo uint32_t APB2LPENR;     /*!< RTODO,     										Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                  */
  __vo uint32_t BDCR;          /*  										Address offset: 0x70 */
  __vo uint32_t CSR;           /*  										Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                  */
  __vo uint32_t SSCGR;         /*  										Address offset: 0x80 */
  __vo uint32_t PLLI2SCFGR;    /*  										Address offset: 0x84 */
  __vo uint32_t PLLSAICFGR;    /*  										Address offset: 0x88 */
  __vo uint32_t DCKCFGR;       /*  										Address offset: 0x8C */
  __vo uint32_t CKGATENR;      /*  										Address offset: 0x90 */
  __vo uint32_t DCKCFGR2;      /*  										Address offset: 0x94 */

} RCC_RegDef_t;

typedef struct
{
	__vo uint32_t IMR;    /*!<         	  	    Address offset: 0x00 */
	__vo uint32_t EMR;    /*             						Address offset: 0x04 */
	__vo uint32_t RTSR;   /*,  									     Address offset: 0x08 */
	__vo uint32_t FTSR;   /*, 										Address offset: 0x0C */
	__vo uint32_t SWIER;  /*,  									   Address offset: 0x10 */
	__vo uint32_t PR;     /*                					   Address offset: 0x14 */

}EXTI_RegDef_t;

/*
 * peripheral register definition structure for SYSCFG
 */
typedef struct
{
	__vo uint32_t MEMRMP;       /*!< Give a short description,                    Address offset: 0x00      */
	__vo uint32_t PMC;          /*!< TODO,     									  Address offset: 0x04      */
	__vo uint32_t EXTICR[4];    /*!< TODO , 									  Address offset: 0x08-0x14 */
	uint32_t      RESERVED1[2];  /*!< TODO          							  Reserved, 0x18-0x1C    	*/
	__vo uint32_t CMPCR;        /*!< TODO         								  Address offset: 0x20      */
	uint32_t      RESERVED2[2];  /*!<                                             Reserved, 0x24-0x28 	    */
	__vo uint32_t CFGR;         /*!< TODO                                         Address offset: 0x2C   	*/
} SYSCFG_RegDef_t;



#define GPIOD  				((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define RCC 				((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI				((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)
#define GPIOD_PCLK_EN()		(RCC->AHB1ENR |= (1 << 3))
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1 << 14))


#define NVIC_ISER0 (*(volatile uint32_t*)0xE000E100)
#define NVIC_EnableIRQ(IRQn)   (NVIC_ISER0 |= (1 << ((uint32_t)(IRQn) & 0x1F)))
