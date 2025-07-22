

#include <stdint.h>
#include "stm32f4xx.h"


/****macros for LED and BUTTON ******/
#define LED1_PIN 12
#define LED2_PIN 13
#define BTN0_PIN 0
#define BTN1_PIN 1
#define NUM_BUTTONS 2

/******** structure for PIN********/

const int led_pins[NUM_BUTTONS] = {LED1_PIN, LED2_PIN};
void EXTI0_IRQHandler(void) ;
void EXTI1_IRQHandler(void);
struct pin
{
int btn_no;
void(*fptr)(int x);
int led_no;
}btn[NUM_BUTTONS];

void delay(int x)
{
	for ( int j=0;j<x;j++);
	}

/*****blink LED 1****/
void blink1(int n)
{
GPIOD->ODR |=(1<<n);
delay(10000);
GPIOD->ODR &= ~(1 << n);
}

/****blink LED 2****/
void blink2(int m)
{
GPIOD->ODR |=(1<<m);
delay(10000);
GPIOD->ODR &= ~(1 << m);
}
void (*fptrarr[])(int n)={blink1,blink2};

/***Initilisation of GPIO,ISR,PIN structure*****/

void GPIO_init(GPIO_RegDef_t* gpio,RCC_RegDef_t * rcc)
{
    // 1. Enable clock for GPIOD
    rcc->AHB1ENR |= (1 << 3);  // Bit 3 = GPIODEN

    // 2. Configure MODER
    // Clear mode bits for PD0, PD1, PD12, PD13
    gpio->MODER &= ~(
        (3 << (2 * 0))  |  // PD0
        (3 << (2 * 1))  |  // PD1
        (3 << (2 * 12)) |  // PD12
        (3 << (2 * 13))    // PD13
    );

    // Set PD12 and PD13 to output mode (01)
    gpio->MODER |= (
        (1 << (2 * 12)) |
        (1 << (2 * 13))
    );

    // 3. Configure OTYPER (output type) for PD12 and PD13
    gpio->OTYPER &= ~(
        (1 << 12) |
        (1 << 13)
    );  // 0 = push-pull

    // 4. Configure PUPDR
    // Clear PD0 and PD1 pull-up/pull-down config
    gpio->PUPDR &= ~((3 << (2 * 0)) | (3 << (2 * 1))); // Clear
    gpio->PUPDR |=  ((2 << (2 * 0)) | (2 << (2 * 1))); // Set pull-down

    }


void ISR_init(RCC_RegDef_t * rcc,SYSCFG_RegDef_t *syscfg,EXTI_RegDef_t *exti )
{
	RCC->APB2ENR |= (1<<14);
EXTI->IMR|=0x00000003;
EXTI->RTSR|=0x00000003;
EXTI->FTSR &= ~(1 << 0);
SYSCFG->EXTICR[0] = 0x00000033;
 RCC->APB2ENR &= ~(1<<14);
NVIC_EnableIRQ(IRQ_NO_EXTI0);
NVIC_EnableIRQ(IRQ_NO_EXTI1);
}


void pin_struct_init()
{
for(int i=0;i<2;i++)
{
btn[i].btn_no=i;
btn[i].fptr=fptrarr[i];
btn[i].led_no=led_pins[i];
}

}

/***main function***/
int main(void)
{
	GPIO_RegDef_t* gpio=GPIOD;
	RCC_RegDef_t * rcc=RCC;
	SYSCFG_RegDef_t *syscfg=SYSCFG;
	EXTI_RegDef_t * exti=EXTI;
	GPIO_init(gpio, rcc);
	ISR_init(rcc,syscfg, exti);
	pin_struct_init();
    /* Loop forever */
	/*if (GPIOD->IDR & (1 << 0)) {
	        GPIOD->ODR |= (1 << 12);
	    } else {
	        GPIOD->ODR &= ~(1 << 12);
	    }




	    */
	for(;;);
}
/***** ISR for GPIO interrupts*****/

void handle_exti(uint8_t line)
 {
    if (EXTI->PR & (1 << line))
	{
        EXTI->PR |= (1 << line);  // Clear pending bit
        btn[line].fptr(btn[line].led_no);
    }
}
void EXTI0_IRQHandler(void)
{
    handle_exti(0);
}

void EXTI1_IRQHandler(void)
{
    handle_exti(1);
}
