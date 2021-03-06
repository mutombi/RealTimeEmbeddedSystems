
#include "stm32f4xx.h"

int main(void) {
	
	// Initalise GPIO port for LEDs
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;		// Enable GPIOD clock
	GPIOD->MODER |= GPIO_MODER_MODER12_0;		// Set GPIOD pin 12 to output
	
	// Initalise Timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;			// Enable timer 2 clock
	TIM2->CR1 &= ~0x00000016;		/* Sets the counter as an upcounter and counter overflow/underflow detection enabled*/
	TIM2->CR1 |= 0x00000008; 	/* Turn off repeat in CR1 - i.e. use one pulse mode */
	TIM2->PSC = 8400 - 1; 			/* Prescaler value - the prescaler clock defaults to twice
	the APB1 which is running at 42MHz - so the timer clock is 84MHz */
	TIM2->ARR = 10000 - 1;	/* sets the value in the auto-reload register */
	TIM2->EGR = 1; 							/* Re-initalises the timer */
	
	
	for(;;){
		GPIOD->BSRR = 1<<12; // Turn on the green LED
		
		TIM2->CR1 |= 1;  //Enables the counter using the register CR1
		while((TIM2->SR&0x0001)!=1){}; //TIM2 to implement a 1 second delay
		TIM2->SR &= ~1; 
			
		GPIOD->BSRR = 1<<(12+16); // Turn off the green LED
		
		TIM2->CR1 |= 1; //Add the correct code //Enables the counter using the register CR1
		while((TIM2->SR&0x0001)!=1){}; 
		TIM2->SR &= ~1;
		
	}

}